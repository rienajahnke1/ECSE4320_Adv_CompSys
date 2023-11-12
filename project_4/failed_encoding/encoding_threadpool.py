import pandas as pd
import threading
import numpy as np
import varint
from concurrent.futures import ThreadPoolExecutor
import time

# Function to perform dictionary encoding and integer compression on a chunk of data
def encode_chunk(chunk, dictionary, result_df):
    chunk['EncodedColumn'] = chunk['RawColumn'].map(dictionary)
    chunk['CompressedEncoded'] = chunk['EncodedColumn'].apply(varint.encode)
    result_df.append(chunk['CompressedEncoded'])

# Function to read chunks of data from the file
def read_chunks(file, chunk_size):
    while True:
        chunk_data = []
        for _ in range(chunk_size):
            line = next(file, None)
            if line is None:
                break
            chunk_data.append(line.strip())

        if not chunk_data:
            break

        yield pd.DataFrame({'RawColumn': chunk_data})

start_time = time.time()

# Load the raw data from a .txt file
file_path = "medbig.txt"
with open(file_path, "r") as file:
    # Strip any leading or trailing whitespace
    raw_data = [line.strip() for line in file]

# Create a DataFrame to store the encoded data
result_df = []

# Create a dictionary to store the mapping
unique_values = list(set(raw_data))
dictionary = {value: index for index, value in enumerate(unique_values)}

# Split the data into chunks for multi-threading
num_threads = 2
chunk_size = 1000000

# Use ThreadPoolExecutor to parallelize reading chunks
with ThreadPoolExecutor(max_workers=num_threads) as executor:
    # Create futures for reading chunks
    futures = {executor.submit(encode_chunk, chunk, dictionary, result_df): chunk
               for chunk in read_chunks(iter(raw_data), chunk_size)}

    # Wait for all threads to finish
    for future in futures:
        future.result()

# Combine the results into a single DataFrame
encoded_data_df = pd.concat(result_df)

end_time = time.time()
total_time = end_time - start_time
print(total_time)

# Save the encoded data to a new file (e.g., a CSV file)
output_file = "encoded_data_file.csv"
encoded_data_df.to_csv(output_file, index=False)

# Optionally, save the dictionary to a separate file
dictionary_file = "dictionary.csv"
pd.DataFrame(list(dictionary.items()), columns=["Value", "Code"]).to_csv(dictionary_file, index=False)
