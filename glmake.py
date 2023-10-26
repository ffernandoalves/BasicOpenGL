make = {
    "project_structure": {
        "extern": "extern",
        "intern": "include",
        "src": "src"
    },
    "compile": {
        "bin_name": "test_gl", # or {'default': 'to use the same name as the main.cpp/hpp file'}
        "compile": "g++", # or gcc
        "compile_version": "-std=c++17", 
        "flags": ["glfw3dll"], # sem o '-l' inicial
        "main_file": "src/main.cpp", # or ["src", "gl.c"]
    }
}