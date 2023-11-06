import pandas as pd
import zstandard as zstd

# Simulated raw data
raw_data = ["apple", "banana", "apple", "cherry", "banana"]

# Create a DataFrame with the raw data
df = pd.DataFrame({"RawColumn": raw_data})

# Dictionary encoding
unique_values = df["RawColumn"].unique()
dictionary = {value: index for index, value in enumerate(unique_values)}
df["EncodedColumn"] = df["RawColumn"].map(dictionary)

# Integer compression using zstandard
cctx = zstd.ZstdCompressor()
compressed_data = cctx.compress(df["EncodedColumn"].to_numpy().tobytes())

# Save dictionary and compressed data to files
with open("dictionary.txt", "w") as dictionary_file:
    for key, value in dictionary.items():
        dictionary_file.write(f"{key}:{value}\n")

with open("compressed_data.zst", "wb") as compressed_data_file:
    compressed_data_file.write(compressed_data)

print("Dictionary encoding and compression completed.")
