import os
import re
import pandas as pd

class MapfileConfig:
    def __init__(self):
        self.list_memory = list()
        self.dict_limit = dict()
        self.list_memory.clear()
        self.dict_limit.clear()
        self.limit_ram = 0
        self.sort_name = 'flash'
        self.sort_type = 'afile'
        self.map_file = os.getenv("SDK_APP_MAP")
        if self.map_file is None:
            self.map_file = './demo.map'
    def codesize(self, sort_name='flash', sort_type='afile'):
        self.list_memory.clear()
        self.dict_limit.clear()
        self.sort_name = sort_name
        self.sort_type = sort_type
        with open(self.map_file, 'r', encoding='UTF-8') as f:
            s = f.read().replace('\r\n', '\n')
            # find memory map (without discard and debug sections)
            if re.findall('Linker script and memory map([\s\S]+?)OUTPUT\(', s):
                mem_map = re.findall('Linker script and memory map([\s\S]+?)OUTPUT\(', s)[0]
            elif re.findall('链结器命令稿和内存映射([\s\S]+?)OUTPUT\(', s):
                mem_map = re.findall('链结器命令稿和内存映射([\s\S]+?)OUTPUT\(', s)[0]
            list_fill = re.findall('(\*fill\*)[ \t]+(0x\w+)[ \t]+(0x\w+)[ \t]+\n', mem_map)
            list_module = re.findall('(0x\w+)[ \t]+(0x\w+)[ \t]+(\S+)\n', mem_map)

            # find the memory configuration
            mem_config_text = '\n'
            # if re.findall('Memory Configuration\n\nName             Origin             Length             Attributes\n([\s\S]+)\nLinker script and memory map', s):
            #    mem_config_text += re.findall('Memory Configuration\n\nName             Origin             Length             Attributes\n([\s\S]+)\nLinker script and memory map', s)[0]
            if re.findall('Attributes\n([\s\S]+)\nLinker script and memory map', s):
                mem_config_text += re.findall('Attributes\n([\s\S]+)\nLinker script and memory map', s)[0]
            elif re.findall('属性\n([\s\S]+)\n链结器命令稿和内存映射', s):
                mem_config_text += re.findall('属性\n([\s\S]+)\n链结器命令稿和内存映射', s)[0]

            # find the RAM configuration
            # ram_config_text = re.findall('\n(RAM\S*)\s+(0x\w+)\s+(0x\w+)\s+xrw\n', mem_config_text)
            ram_config_text = re.findall('\n(\S+)\s+(0x\w+)\s+(0x\w+)', mem_config_text)

            if (len(ram_config_text)) == 0:
                print('no memory definite address hint')
            else:
                # get every RAM configuration's  start - end address
                ram_config = []
                for ram in ram_config_text:
                    ram_config += [{'name': ram[0], 'start': int(ram[1], 16), 'end': int(ram[1], 16) + int(ram[2], 16),
                                    'limit': int(ram[2], 16)}]
                    self.limit_ram += int(ram[2], 16)

        df0 = pd.DataFrame(data=list_module, columns=["address", "size", "module"])
        df1 = pd.DataFrame(data=list_module, columns=["address", "size", "module"])
        df2 = pd.DataFrame(data=list_fill, columns=["module", "address", "size"])

        f0 = lambda x: int(str(x), 16)
        f1 = lambda x: os.path.split(re.sub(u"\\(.*?\\)", "", x))[1]
        f2 = lambda x: re.findall(r"(.*\.a)", x)[0] if re.findall(r"(.*\.a)", x) else float('nan')
        f3 = lambda x: re.findall(r"[(](.*)[)]", x)[0] if re.findall(r"[(](.*)[)]", x) else os.path.split(x)[1]

        df0['module'] = df0["module"].agg(f1)
        df0['size'] = df0['size'].agg(f0)
        df0['address'] = df0['address'].agg(f0)

        df1['name'] = df1["module"].agg(f3)
        df1['module'] = df1["module"].agg(f1)
        df1['size'] = df1['size'].agg(f0)
        df1['address'] = df1['address'].agg(f0)

        df2['size'] = df2['size'].agg(f0)
        df2['address'] = df2['address'].agg(f0)

        df0 = df0.append(df2, ignore_index=True, sort=True)
        df1 = df1.append(df2, ignore_index=True, sort=True)

        list_ram = ["module"]
        for ram_info in ram_config:
            if 'default' in ram_info['name']:
                continue
            else:
                list_ram.append(ram_info['name'])
            # print(ram_info['name'], ram_info['limit'])
            self.dict_limit[ram_info['name']] = ram_info['limit']
            self.list_memory.append(ram_info['name'])
            df0[ram_info['name']] = df0.apply(
                lambda x: 0 if x['address'] < ram_info['start'] or x['address'] > ram_info['end'] else x['size'],
                axis=1)
            df1[ram_info['name']] = df1.apply(
                lambda x: 0 if x['address'] < ram_info['start'] or x['address'] > ram_info['end'] else x['size'],
                axis=1)
        df = None
        if self.sort_type == "afile":
            df = df0.groupby('module')[self.list_memory].sum()
            summary = df.sum()
            # print(summary)
            df.sort_values(self.sort_name, ascending=False, inplace=True)
            df.loc['total'] = summary
            df.loc['limit'] = pd.Series(self.dict_limit)
            df = df.reset_index()
            df.index = list(range(1, len(df) - 1)) + ["", ""]
        elif self.sort_type == "ofile":
            df = df1.groupby(['module', 'name'])[self.list_memory].sum()
            summary = df.sum()
            df.sort_values(self.sort_name, ascending=False, inplace=True)
            # df.loc['total'] = summary
            # df.loc['limit'] = pd.Series(self.dict_limit)
            df = df.reset_index()
            df.index = list(range(1, len(df) + 1))
            df.loc['total'] = df.apply(lambda x: x.sum())
            self.dict_limit['module'] = ""
            self.dict_limit['name'] = ""
            df.loc['limit'] = pd.Series(self.dict_limit)
            df.loc['total', 'module'] = ""
            df.loc['total', 'name'] = ""

        pd.set_option('display.max_colwidth', 999)
        pd.set_option('display.max_rows', 999)
        print(f'======================= Sort {self.sort_type} on {self.sort_name}=======================')
        print(str(df))


mapConfig = MapfileConfig()
#mapConfig.codesize(sort_name='ram_wifi', sort_type='ofile')
#mapConfig.codesize(sort_name='ram_tcm', sort_type='ofile')
mapConfig.codesize(sort_name='flash', sort_type='ofile')
mapConfig.codesize(sort_name='flash', sort_type='afile')

