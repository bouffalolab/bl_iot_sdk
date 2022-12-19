# Core dump

在系统异常时dump出指定的内存数据

## 功能

1. 可选配置默认dump区域，在exception时自动dump至UART，通过串口工具保存
2. 输出端口可配（用户自行适配）：
  - 串口
  - flash
  - spi

3. base64加密编码输出

## 结构

1. Dump Tool命令


| type     | header | operation | *data | operation | *data | stop |
| -------- | ------ | --------- | ----- | --------- | ----- | ---- |
| **len**  | 1      | 1         | 4     | 1         | 4     | 1    |
| **data** | $      | command   | addr  | command   | len   | #    |

operation支持以下命令：

> 所有命令均为字符型

| command | info             |
| ------- | ---------------- |
| d       | dump默认内存区域 |
| x       | 指定dump地址     |
| l       | 指定dump长度     |
| ...     |                  |

**注：**

- **x和l参数成对传入，先传入x，再传入l，若未提供l，默认dump长度为0x1000**
- **一次命令仅可包含一对`addr/len`**
- **若未配置默认dump区域，d命令不会响应；传入d命令时，其他指令会被忽略**



2. dump data

| header                            | data | crc stop              |
| --------------------------------- | ---- | --------------------- |
| ------ DATA BEGIN addr@len ------ | ***  | ------ END crc ------ |

CRC为解码后原数据的CRC，不是base64编码的CRC
