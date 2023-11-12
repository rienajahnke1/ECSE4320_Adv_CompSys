import pandas as pd
import threading
import numpy as np
import varint
import time

# Function to perform dictionary encoding and integer compression on a chunk of data
def encode_chunk(chunk, dictionary, result_df):
    chunk['EncodedColumn'] = chunk[0].map(dictionary)
    chunk['CompressedEncoded'] = chunk['EncodedColumn'].apply(varint.encode)
    #result_df.append(chunk['CompressedEncoded'])
    result_df.append(chunk['EncodedColumn'])

start_time = time.time()

# Load the raw data from a .txt file
file_path = "medbig.txt"
with open(file_path, "r") as file:
    raw_data = file.readlines()

# Strip any leading or trailing whitespace
raw_data = [line.strip() for line in raw_data]

# Create a DataFrame to store the encoded data
result_df = []

# Create a dictionary to store the mapping
unique_values = list(set(raw_data))
dictionary = {value: index for index, value in enumerate(unique_values)}

# Split the data into chunks for multi-threading
num_threads = 12
chunk_size = len(raw_data) // num_threads
threads = []

# Create and start multiple threads
for i in range(num_threads):
    start = i * chunk_size
    end = (i + 1) * chunk_size if i < num_threads - 1 else len(raw_data)
    
    # Create a DataFrame
    chunk_data = {0: raw_data[start:end]}
    chunk = pd.DataFrame(chunk_data)
    
    thread = threading.Thread(target=encode_chunk, args=(chunk, dictionary, result_df))
    thread.start()
    threads.append(thread)

# Wait for all threads to finish
for thread in threads:
    thread.join()

# Combine the results into a single DataFrame
encoded_data_df = pd.concat(result_df)

# Save the encoded data to CSV file
output_file = "encoded_data_file.csv"
encoded_data_df.to_csv(output_file, index=False)

# Save the dictionary to a separate file
dictionary_file = "dictionary.csv"
pd.DataFrame(list(dictionary.items()), columns=["Value", "Code"]).to_csv(dictionary_file, index=False)

end_time = time.time()
total_time = end_time - start_time
print(total_time)
