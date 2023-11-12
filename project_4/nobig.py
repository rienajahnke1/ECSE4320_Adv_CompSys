"""
import pandas as pd
import threading

import numpy as np
import varint

# Function to perform dictionary encoding and integer compression on a chunk of data
def encode_chunk(chunk, dictionary, result_df):
    chunk['EncodedColumn'] = chunk[0].map(dictionary)
    chunk['CompressedEncoded'] = chunk['EncodedColumn'].apply(varint.encode)
    #result_df.append(chunk['CompressedEncoded'])
    result_df.append(chunk['EncodedColumn'])

# Load the raw data from a .txt file
file_path = "medium.txt"
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
    
    # Create a DataFrame with the first (and only) column
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

# Save the encoded data to a new file (e.g., a CSV file)
output_file = "encoded_data_file.csv"
encoded_data_df.to_csv(output_file, index=False)

# Optionally, save the dictionary to a separate file
dictionary_file = "dictionary.csv"
pd.DataFrame(list(dictionary.items()), columns=["Value", "Code"]).to_csv(dictionary_file, index=False)

"""

import pandas as pd
import varint
import concurrent.futures
import time

# Function to perform dictionary encoding and integer compression on a chunk of data
def encode_chunk(chunk, dictionary):
    chunk = chunk.copy()  # Explicitly create a copy
    chunk['EncodedColumn'] = chunk['RawColumn'].map(dictionary)
    chunk['CompressedEncoded'] = chunk['EncodedColumn'].apply(varint.encode)
    return chunk[['CompressedEncoded']]


# Load the raw data from a .txt file
file_path = "Column.txt"
df = pd.read_csv(file_path, header=None, names=['RawColumn'])

# Create a dictionary to store the mapping
unique_values = df['RawColumn'].unique()
dictionary = {value: index for index, value in enumerate(unique_values)}

# Split the data into chunks for multi-threading
num_threads = 2
chunk_size = 500000
chunks = [df.iloc[i:i+chunk_size] for i in range(0, len(df), chunk_size)]

start_time = time.time()

# Use ThreadPoolExecutor to parallelize encoding
with concurrent.futures.ThreadPoolExecutor(max_workers=num_threads) as executor:
    results = list(executor.map(encode_chunk, chunks, [dictionary]*num_threads))

# Combine the results into a single DataFrame
encoded_data_df = pd.concat(results)

# Save the encoded data to a new file (e.g., a CSV file)
output_file = "encoded_data_file.csv"
encoded_data_df.to_csv(output_file, index=False)

# Optionally, save the dictionary to a separate file
dictionary_file = "dictionary.csv"
pd.DataFrame(list(dictionary.items()), columns=["Value", "Code"]).to_csv(dictionary_file, index=False)

end_time = time.time()
total_time = end_time - start_time
print(total_time)
