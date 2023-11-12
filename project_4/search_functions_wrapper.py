import ctypes
import numpy as np

# Load the C library
search_functions_lib = ctypes.CDLL('/home/rienajahnke/Adv_CompSys/ECSE4320_Adv_CompSys/project_4/search_functions.so')

"""
# Define the function signature
search_functions_lib.count_and_find_indices.argtypes = [
    ctypes.c_char_p,   # encoded_data
    ctypes.c_int,       # search_key
    ctypes.POINTER(ctypes.c_int),  # indices
    ctypes.c_int,       # dataSize
    ctypes.c_int,       # search_key_len
]
search_functions_lib.count_and_find_indices.restype = ctypes.c_int

def count_and_find_indices(encoded_data, search_key):
    # Convert the Pandas Series to a bytes object
    encoded_data_bytes = encoded_data.astype('int32').tobytes()

    dataSize = len(encoded_data_bytes) // ctypes.sizeof(ctypes.c_int)
    search_key_len = 1  # Assuming search_key is a single integer
    
    # Prepare indices array
    indices = (ctypes.c_int * dataSize)()

    # Call the C function
    matches = search_functions_lib.count_and_find_indices(
        encoded_data_bytes,
        search_key,
        indices,
        dataSize,
        search_key_len
    )

    # Convert indices to a Python list
    indices_list = list(indices)[:matches]

    return matches, indices_list
"""

search_functions_lib.find_indices.argtypes = [
    np.ctypeslib.ndpointer(dtype=np.int32, ndim=1, flags='C_CONTIGUOUS'),  # encoded_data
    ctypes.c_int,     # search_key
    np.ctypeslib.ndpointer(dtype=np.int32, ndim=1, flags='C_CONTIGUOUS'),  # indices
    ctypes.c_int      # dataSize
]
search_functions_lib.find_indices.restype = ctypes.c_int

def find_indices(encoded_data, search_key, indices):
    dataSize = len(encoded_data)

    # Call the C function
    matches = search_functions_lib.find_indices(
        encoded_data,
        search_key,
        indices,
        dataSize
    )

    return matches

