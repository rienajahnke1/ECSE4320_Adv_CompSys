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
file_path = "medbig.txt"
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

# Save the encoded data to a new Feather file
output_file_feather = "encoded_data_file.feather"
encoded_data_df.to_feather(output_file_feather)

# Optionally, save the dictionary to a separate file
dictionary_file = "dictionary.csv"
pd.DataFrame(list(dictionary.items()), columns=["Value", "Code"]).to_csv(dictionary_file, index=False)

end_time = time.time()
total_time = end_time - start_time
print(total_time)


