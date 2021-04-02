-- bit32 = require 'bit32'

function stringToTable( sta )
    local tablesta = {}
    local i
    for i=1, #sta do
        tablesta[i] = sta:byte(i)
    end

    return tablesta
end

function tableTostring(cmd)
    local ret=""
    local i
    for i=1,#cmd do
        ret=ret..string.char(cmd[i])
    end
    return ret
end

function tableToHex(cmd)
    local ret=""
    local i
    for i=1,#cmd do
        ret=ret..string.format("%02X", cmd[i])
    end
    return ret
end

function stringToHexstring(str)
    local ret = ''
    for i=1, #str do
        ret = ret .. string.format("%02x", str:byte(i))
    end
    return ret
end

function stringtoByteArray(str)
    local byteArray  = {}
    local ret = str
    for i=1, #ret do
        byteArray[i] = tonumber(string.format("%02x", ret:byte(i)),16)
    end
    
    return byteArray
end

-- function bitSet(num, idx)
--     return bit32.band(num, bit32.lshift(1, idx)) ~= 0
-- end

function getJD_KVTable(t)
    return getKVTable(t,'stream_id','current_value')
end

function makeJD_KVArray(t)
    return makeKVArray(t,'stream_id','current_value')
end

function decode(cmd)
    local tb
    if cjson == nil then    
        -- FIXME module name is JSON in JD cloud
        -- cjson = (require 'json')
        cjson = (require 'JSON')
        tb = cjson:decode(cmd)
    else
        tb = cjson.decode(cmd)
    end
    return tb
end

function getKVTable(t,keyName,valueName)
    local kvTable = {}
    for i=1, #t do
        key = t[i][''..keyName]
        val = t[i][''..valueName]
        kvTable[''..key] = val
    end
    return kvTable
end

function makeKVArray(t,keyName,valueName)
    local resultArray = {}
    local i=1
    for k,v in pairs(t) do
        resultArray[i] = {}
        resultArray[i][''..keyName] = k
        resultArray[i][''..valueName] = v
        i = i+1
    end
    return resultArray
end

function serializeArray(arrayObj)
    local jsonStr = "["
    for i=1,#arrayObj do
        jsonStr = jsonStr..serialize(arrayObj[i])..','
    end
    local jsonItemStrLen =  string.len(jsonStr)-1;
    jsonStr = string.sub(jsonStr,1,jsonItemStrLen)
    jsonStr = ''..jsonStr..']'
    return jsonStr
end

function serialize(obj)  
    local lua = ""  
    local t = type(obj)  
    if t == "number" then  
        lua = lua .. obj  
    elseif t == "boolean" then  
        lua = lua .. tostring(obj)  
    elseif t == "string" then  
        lua = lua .. string.format("%q", obj)  
    elseif t == "table" then  
        lua = lua .. "{"  
    for k, v in pairs(obj) do  
   --lua = lua .. "[" .. serialize(k) .. "]=" .. serialize(v) .. ",\n"  
        lua = lua .. serialize(k) .. ":"..serialize(v) .. ","  
    end  
    local metatable = getmetatable(obj)  
        if metatable ~= nil and type(metatable.__index) == "table" then  
        for k, v in pairs(metatable.__index) do  
            --lua = lua .. "[" .. serialize(k) .. "]=" .. serialize(v) .. ",\n"  
            lua = lua .. serialize(k) .. ":"..serialize(v) .. ","  
        end  
    end  
    local luaLen =  string.len(lua)-1;
    lua = string.sub(lua,1,luaLen)
    lua = lua .. "}"  
    elseif t == "nil" then  
        return nil  
    else  
        error("can not serialize a " .. t .. " type.")  
    end  
    return lua  
end 

function table2json(t)
    local function serialize(tbl)
        local tmp = {}
        for k, v in pairs(tbl) do
        local k_type = type(k)
        local v_type = type(v)
            local key = (k_type == "string" and "\"" .. k .. "\":") 
            or (k_type == "number" and "")
            local value = (v_type == "table" and serialize(v))
            or (v_type == "boolean" and tostring(v))
            or (v_type == "string" and "\"" .. v .. "\"")
            or (v_type == "number" and v)
            tmp[#tmp + 1] = key and value and tostring(key) .. tostring(value) or nil
        end
        if table.maxn(tbl) == 0 then
            return "{" .. table.concat(tmp, ",") .. "}"
        else
            return "[" .. table.concat(tmp, ",") .. "]"
        end
    end
    assert(type(t) == "table")
    return serialize(t)
end

function jds2pri( bizcode, cmd )
    --return err, length, bin
    local bin = {0xA5, 0xA5, 0x5A, 0x5A, -- @1,  帧头
           0x00, 0x00,             -- @5,  校验和，这里不计算，留给Wi-Fi模组计算
           0x02, 0x00,             -- @7,  帧命令，这里是SET_STATUS
           0x18, 0x00, 0x00, 0x00,  -- @9,  帧长
           0x10, 0x01,             -- @13, 协议版本号，产品类型
           0x00,                   -- @15, 开关机
           0x00,                   -- @16, 微波/微波+蒸汽
           0x00,                   -- @17, 光波
           0x00,                   -- @18, 智能三宝
           0x00,                   -- @19, 组合
           0x00,                   -- @20, 菜单选择
           0x00,                   -- @21, 重量/份量选择
           0x00,                   -- @22, 定时功能开关
           0x00,                   -- @23, （预约功能）小时/定时功能为分钟
           0x00,                   -- @24, （预约时）分钟/（定时功能为秒）
           0x00,                   -- @25, 语音开关
           0x00,                   -- @26, 童锁开关
           0x00,                   -- @27, 报警信息
           0x00,                   -- @28, 设置工作时间分钟
           0x00,                   -- @29, 设置工作时间秒
           0x00,                   -- @30, 设备状态
           0x00,                   -- @31, 当前时钟 小时，留给Wi-Fi模组填充
           0x00,                   -- @32, 当前时钟 分钟
           0x00,                   -- @33, 当前时制
           0x00,                   -- @34, 酸奶工作时间补充位
           0x00,                   -- @35, 工作模式
           0x00,                   -- @36, 预留
    }

    if bizcode == 1002 then
        local json = decode(cmd)
        local streams = json["streams"]
        local tabstreams = getJD_KVTable(streams)
        local snapshot = json["snapshot"]
        local tabsnapshot = getJD_KVTable(snapshot)


        -- XXX Using snapshot to build command might NOT be corrent.
        -- This is only for demo purpose.
        for k, v in pairs(tabstreams) do
            tabsnapshot[k] = v
        end

        local t
        t = tabsnapshot['Mode']
        if t == '2' then -- 微波
            bin[35] = 2
        end
        if tabstreams['Mode'] ~= nil then
            bin[#bin + 1] = 35
            bin[#bin + 1] = 2
        end

        bin[28] = tonumber(tabsnapshot['WorkTimeSetMinute'])
        bin[29] = tonumber(tabsnapshot['WorkTimeSetSecond'])
        if tabstreams['WorkTimeSetMinute'] ~= nil then
            bin[#bin + 1] = 28
            bin[#bin + 1] = bin[28]
        end
        if tabstreams['WorkTimeSetSecond'] ~= nil then
            bin[#bin + 1] = 29
            bin[#bin + 1] = bin[29]
        end

        t = tabsnapshot['Work']
        if t == '0' then
            bin[15] = 1  --启动
        elseif t == '1' then
            bin[15] = 3  --取消
        elseif t == '2' then
            bin[15] = 2  --暂停
        elseif t == '3' then
            bin[15] = 0  --待机
        elseif t == '4' then
            bin[15] = 4  --预约
        end
        if tabstreams['Work'] ~= nil then
            bin[#bin + 1] = 15
            bin[#bin + 1] = bin[15]
        end

        t = tabsnapshot['Microwave']
        if t == '0' then
            bin[16] = 0
        elseif t == '1' then
            bin[16] = 2
        elseif t == '2' then
            bin[16] = 4
        elseif t == '3' then
            bin[16] = 6
        elseif t == '4' then
            bin[16] = 8
        elseif t == '5' then
            bin[16] = 0xA
        elseif t == '6' then
            bin[16] = 0x5A
        end
        if tabstreams['Microwave'] ~= nil then
            bin[#bin + 1] = 16
            bin[#bin + 1] = bin[16]
        end

    elseif bizcode == 1004 then --获取快照
        bin[7] = 1
    else                --错误的code指令,返回获取快照
        bin[7] = 1
    end

    local ret = tableToHex(bin)
    local len = string.len(ret)
    return 0, len, ret
end

function pri2jds( bizcode, length, bin )
    --return err, jstr, bizcode
    bin = stringtoByteArray(bin)
    local jdstr

    local result = {
        Work = '0',
        Mode = '0',
        State = '0',
        Microwave = '0',
        WorkTimeRemainingMinute = '0',
        WorkTimeRemainingSecond = '0',
    }

    local t, v

    t = bin[15]
    v = 3  --待机
    if t == 0 then
        v = 3  --待机
    elseif t == 1 then
        v = 0  --启动
    elseif t == 2 then
        v = 2  --暂停
    elseif t == 3 then
        v = 1  --取消
    elseif t == 4 then
        v = 4  --预约
    end
    v = tostring(v)
    result.Work = v

    t = bin[35]
    v = 0  --自定义
    if t == 2 then
        v = 2  --微波
    end
    v = tostring(v)
    result.Mode = v

    t = bin[30]
    v = 0  --未制作
    -- FIXME, judge bit
    if t == 16 then
        v = 1  --制作中
    else
        v = 0  --未制作
    end
    v = tostring(v)
    result.State = v

    t = bin[16]
    v = 0
    if t == 0 then
        v = 0  --风冷
    elseif t == 2 then
        v = 1  --低火
    elseif t == 4 then
        v = 2  --中低火
    elseif t == 6 then
        v = 3  --中火
    elseif t == 8 then
        v = 4  --中高火
    elseif t == 0xA then
        v = 5  --高火
    elseif t == 0x5A then
        v = 6  --蒸汽
    end
    v = tostring(v)
    result.Microwave = v

    result.WorkTimeRemainingMinute = tostring(bin[28])
    result.WorkTimeRemainingSecond = tostring(bin[29])


    result = makeJD_KVArray(result)
    result = serializeArray(result)

    if bin[1] == 0xA5 and bin[2] == 0xA5 and bin[3] == 0x5A and bin[4] == 0x5A then
        jdstr = '{"code":0,"streams":'..result..',"msg":"done"}'
    else
        jdstr = '{"code":0,"streams":[],"msg":"done"}'
    end

    return 0, jdstr, bizcode
end
