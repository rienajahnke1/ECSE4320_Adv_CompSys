# main.py
from search_functions import find_in_dictionary, count_and_find_indices
import varint
import pandas as pd
import numpy as np

# Load the dictionary
dictionary_df = pd.read_csv("dictionary.csv")
dictionary = list(dictionary_df['Value'])

# Find the encoded value for the search string
search_string = input("Enter the string to search: ")
key_index = find_in_dictionary(search_string, dictionary)

if key_index == -1:
    print(f"Search string '{search_string}' not found in the dictionary.")
else:
    # Encode the varint-encoded value
    encoded_value = varint.encode(dictionary_df.at[key_index, 'Code'])

    # Load the encoded data from the Feather file
    encoded_data_df = pd.read_feather("encoded_data_file.feather")
    encoded_data = np.array(encoded_data_df['CompressedEncoded'].to_list(), dtype=np.uint8)

    # Prepare arrays to store indices and occurrences
    indices = np.empty(len(encoded_data), dtype=np.int32)
    occurrences = np.empty(1, dtype=np.int32)

    # Use SIMD to count occurrences and find indices
    count_and_find_indices(encoded_data, encoded_value, indices, occurrences)

    if occurrences[0] == 0:
        print(f"No occurrences of the encoded value {encoded_value} found in the encoded data.")
    else:
        print(f"Occurrences of the encoded value {encoded_value} found at indices: {indices[:occurrences[0]]}")









# main.py

import pandas as pd
import varint
from search_functions_wrapper import count_and_find_indices

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

    # Find the rows with the encoded value in the 'CompressedEncoded' column
    indices = count_and_find_indices(encoded_data_df['CompressedEncoded'].to_numpy().tobytes(), encoded_value)

    if not indices[1]:
        print(f"No occurrences of the encoded value {encoded_value} found in the encoded data.")
    else:
        print(f"Occurrences of the encoded value {encoded_value} found at indices: {indices[1]}")

# Replace these file paths with your actual file paths
dictionary_file_path = "dictionary.csv"
encoded_data_file_path = "encoded_data_file.feather"

# Get the search string from the user
search_string = input("Enter the string to search: ")

# Perform the search and decoding
find_and_decode(search_string, dictionary_file_path, encoded_data_file_path)





