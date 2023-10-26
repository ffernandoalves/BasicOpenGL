import os
import pathlib
import subprocess
import logging

# constants
ROOT_DIR = pathlib.Path(".").absolute()

# final project structure
tree_result = {
    "build": [
        "bin", "deps", "logs"
    ]
}

# logger
log_format = "[%(asctime)s][%(name)s][%(levelname)s]: %(message)s"
folder_log = ROOT_DIR/'build'/'logs'
logging_filename = "glcompile.log"
logging.basicConfig(format=log_format,
                    filename=folder_log/logging_filename,
                    level=logging.INFO,
                    datefmt='%m/%d/%Y %I:%M:%S %p')
logger = logging.getLogger("glcompile")
logger.setLevel(logging.DEBUG)
ch = logging.StreamHandler()
ch.setLevel(logging.DEBUG)
ch.setFormatter(logging.Formatter(log_format))
logger.addHandler(ch)

def create_tree_result():
    """create compilation folders"""
    
    all_dirs = []
    for _father_dir, _child_dirs in tree_result.items():
        all_dirs += [ROOT_DIR/_father_dir]
        for _sub_dir in _child_dirs:
            all_dirs += [ROOT_DIR/_father_dir/_sub_dir]
                
    for d in all_dirs:
        if (not d.exists()):
            mkdir(d)
        else:
            logger.info(f"The '{d}' folder already exists.")
            
create_tree_result()

def mkdir(dirpath: str):
    try:
        dirpath = pathlib.Path(dirpath)
        dirpath.mkdir()
        logger.info(f"Folder \'{dirpath.absolute()}\' was created successfully.")
    except:
        logger.exception(f"Could not create \'{dirpath.absolute()}\' folder.")
        raise
        
def exec_cmd(compile_bin: pathlib.Path, args: list):
    kwargs = {
        "stdin": subprocess.PIPE,
        "stderr": subprocess.STDOUT,
        "stdout": subprocess.PIPE,
        "startupinfo": None,
        "text": True,
        "env": os.environ,
    }
    
    cmd_args = [compile_bin]
    cmd_args += args
    proc = subprocess.run(cmd_args, **kwargs)
    return proc

def compile():
    proc = exec_cmd(compile_bin="C:\\msys64\\mingw64\\bin\\g++.exe", args=['--version'])
    args = " ".join(proc.args)
    returncode = proc.returncode
    stdout = proc.stdout
    stderr = proc.stderr
    
    logger.info(f"Comando executado: {args}")
    logger.info(stdout)

if __name__ == "__main__":
    compile()
    