import pandas as pd
import dask.dataframe as dd
import dask.multiprocessing
import varint
import time

# Function to perform dictionary encoding and integer compression on a chunk of data
def encode_chunk(chunk, dictionary):
    chunk['EncodedColumn'] = chunk['RawColumn'].map(dictionary)
    chunk['CompressedEncoded'] = chunk['EncodedColumn'].apply(varint.encode)
    return chunk[['CompressedEncoded']]


start_time = time.time()

# Load the raw data from a .txt file using Dask
file_path = "medbig.txt"
df = dd.read_csv(file_path, header=None, names=['RawColumn'], blocksize=500000)

# Create a dictionary to store the mapping
unique_values = df['RawColumn'].unique().compute()
dictionary = {value: index for index, value in enumerate(unique_values)}

# Use Dask to parallelize encoding
encoded_data_df = df.map_partitions(encode_chunk, dictionary=dictionary, meta={'CompressedEncoded': 'object'})

# Save the encoded data to a new file (e.g., a CSV file)
output_file = "encoded_data_file.csv"
encoded_data_df.compute().to_csv(output_file, index=False)

# Optionally, save the dictionary to a separate file
dictionary_file = "dictionary.csv"
pd.DataFrame(list(dictionary.items()), columns=["Value", "Code"]).to_csv(dictionary_file, index=False)

end_time = time.time()
total_time = end_time - start_time
print(total_time)
