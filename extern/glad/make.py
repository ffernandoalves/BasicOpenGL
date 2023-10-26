make = {
    "project_structure": {
        "intern": "include",
        "src": "src"
    },
    "compile": {
        "bin_name": None, # or {'default': 'to use the same name as the main.cpp/hpp file'}
        "compile": "g++", # or gcc
        "compile_version": "-std=c++20", 
        "flags": [],
        "main_file": "src/gl.c", # or ["src", "gl.c"]
        "static": True
    }
}