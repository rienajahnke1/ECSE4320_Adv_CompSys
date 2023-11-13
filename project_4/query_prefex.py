import pandas as pd
import varint
import time

def find_and_decode(search_string, dictionary_file, encoded_data_file):
    # Load the dictionary
    dictionary_df = pd.read_csv(dictionary_file)

    # Find the encoded value for the search string
    values = dictionary_df[dictionary_df['Value'].str.contains(search_string, case=False)]['Code'].values
    if len(values) == 0:
        print(f"Search string '{search_string}' not found in the dictionary.")
        return

    # Encode the varint-encoded values
    encoded_values = [varint.encode(val) for val in values]

    # Load the encoded data from the Feather file
    encoded_data_df = pd.read_feather(encoded_data_file)

    # Convert 'CompressedEncoded' column to hexadecimal representation
    # This is to avoid UnicodDecodeError
    encoded_data_df['CompressedEncoded'] = encoded_data_df['CompressedEncoded'].apply(lambda x: x.hex())

    # Find the rows with the encoded values in the 'CompressedEncoded' column
    indices = []
    for encoded_value in encoded_values:
        hex_encoded_value = encoded_value.hex()
        indices.extend(encoded_data_df[encoded_data_df['CompressedEncoded'].str.contains(hex_encoded_value)]['CompressedEncoded'].index.tolist())

    if not indices:
        print(f"No occurrences of the encoded values {encoded_values} found in the encoded data.")
    else:
        print(f"Occurrences of the encoded values {encoded_values} found at indices: {indices}")

dictionary_file_path = "dictionary.csv"
encoded_data_file_path = "encoded_data_file.feather"

# Get the search string from the user
search_string = input("Enter the string to search: ")

start_time = time.time()

# Perform the search and decoding
find_and_decode(search_string, dictionary_file_path, encoded_data_file_path)

end_time = time.time()
total_time = end_time - start_time
print(total_time)
