import pandas as pd
import varint
import numpy as np
from search_functions_wrapper import find_indices

def find_and_decode(search_string, dictionary_file, encoded_data_file):
    # Load the dictionary
    dictionary_df = pd.read_csv(dictionary_file)

    # Find the encoded value for the search string
    value = dictionary_df[dictionary_df['Value'] == search_string]['Code'].values
    if len(value) == 0:
        print(f"Search string '{search_string}' not found in the dictionary.")
        return

    # Encode the varint-encoded value
    encoded_value = varint.encode(value.item())

    # Load the encoded data from the Feather file
    encoded_data_df = pd.read_feather(encoded_data_file)
    
    # Create an array to store the indices
    indices = [0] * len(encoded_data_df['CompressedEncoded'])

    # Find the indices of the compressed key in the compressed data
    indices_list = find_indices(encoded_data_df['CompressedEncoded'].nbytes().to_numpy(), encoded_value, indices)

    if not indices_list:
        print(f"No occurrences of the encoded value {encoded_value} found in the encoded data.")
    else:
        print(f"Occurrences of the encoded value {encoded_value} found at indices: {indices}")


dictionary_file_path = "dictionary.csv"
encoded_data_file_path = "encoded_data_file.feather"

# Get the search string from the user
search_string = input("Enter the string to search: ")

# Perform the search and decoding
find_and_decode(search_string, dictionary_file_path, encoded_data_file_path)
