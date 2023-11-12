import pandas as pd
from concurrent.futures import ProcessPoolExecutor
import time
import varint

"""
# Function to perform dictionary encoding and integer compression on a chunk of data
def encode_chunk(chunk_list, dictionary):
    result_df = pd.DataFrame()
    for chunk_data in chunk_list:
        if isinstance(chunk_data, dict) and 'RawColumn' in chunk_data:
            chunk_data['EncodedColumn'] = chunk_data['RawColumn'].map(dictionary)
            chunk_data['CompressedEncoded'] = chunk_data['EncodedColumn'].apply(varint.encode)
            result_df = pd.concat([result_df, chunk_data[['CompressedEncoded']]], ignore_index=True)
    return result_df
"""
def encode_chunk(chunk_data, dictionary):
    if chunk_data:
        df = pd.DataFrame({'RawColumn': chunk_data})
        df['EncodedColumn'] = df['RawColumn'].map(dictionary)
        df['CompressedEncoded'] = df['EncodedColumn'].apply(varint.encode)
        return df[['CompressedEncoded']]
    return None


# Function to read chunks of data from the file
def read_chunks(file, chunk_size):
    while True:
        chunk_data = [line.strip() for line in (next(file, None) for _ in range(chunk_size)) if line is not None]
        if not chunk_data:
            break
        yield chunk_data


# Load the raw data from a .txt file
file_path = "medbig.txt"
with open(file_path, "r") as file:
    raw_data = [line.strip() for line in file]

# Create a DataFrame to store the encoded data
result_df = []

# Create a dictionary to store the mapping
unique_values = list(set(raw_data))
dictionary = {value: index for index, value in enumerate(unique_values)}

# Split the data into chunks for multi-processing
num_processes = 4
chunk_size = 500000

start_time = time.time()

# Use ProcessPoolExecutor to parallelize reading chunks
with ProcessPoolExecutor(max_workers=num_processes) as executor:
    # Create futures for reading chunks
    futures = {executor.submit(encode_chunk, chunk, dictionary): chunk
               for chunk in read_chunks(iter(raw_data), chunk_size)}

    # Collect the results
    for future in futures:
        encoded_chunk = future.result()
        if encoded_chunk is not None:
            result_df.append(encoded_chunk)

if result_df:
    # Combine the results into a single DataFrame
    encoded_data_df = pd.concat(result_df)

    # Save the encoded data to a CSV file
    output_file = "encoded_data_file.csv"
    encoded_data_df.to_csv(output_file, index=False)

    # Save the dictionary to a separate file
    dictionary_file = "dictionary.csv"
    pd.DataFrame(list(dictionary.items()), columns=["Value", "Code"]).to_csv(dictionary_file, index=False)
else:
    print("No data to process.")
    
end_time = time.time()
total_time = end_time - start_time
print(total_time)
