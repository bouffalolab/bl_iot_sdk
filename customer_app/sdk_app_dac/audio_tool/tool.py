    
import os
import sys
import numpy as np
import math

if __name__ == "__main__":
    data_list_deal = []
    path =  sys.argv[1] 
    path_save = sys.argv[2] 

    open_file = open(path,"rb")
    save_file = open(path_save,"wb")

    data_list_deal = []
    data_list_u16 = []


    for i in range(os.path.getsize(path)//2):
        data = open_file.read(2)
        data_int = int.from_bytes(data, byteorder='little', signed=True)
        data_int = int((data_int +32768 ) * 0.0156099794003204)
        data_list_u16.append(data_int.to_bytes(2, byteorder='little', signed=False))

    res_arr = np.array(data_list_u16)

    save_file.write(res_arr)
    save_file.close()