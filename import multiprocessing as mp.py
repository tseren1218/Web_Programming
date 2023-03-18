import multiprocessing as mp
import os
import time

def writer(shared_array):
    """Write to the shared memory array."""
    for i in range(len(shared_array)):
        shared_array[i] = os.getpid()
        time.sleep(0.1)

def reader(shared_array):
    """Read from the shared memory array."""
    while True:
        print(f"Reader process {os.getpid()}: {shared_array[:]}")
        time.sleep(0.5)

if __name__ == "__main__":
    # Create a shared memory array
    shared_array = mp.RawArray('i', 10)

    # Start the writer process
    writer_process = mp.Process(target=writer, args=(shared_array,))
    writer_process.start()

    # Start the reader process
    reader_process = mp.Process(target=reader, args=(shared_array,))
    reader_process.start()

    # Wait for both processes to finish
    writer_process.join()
    reader_process.join()
