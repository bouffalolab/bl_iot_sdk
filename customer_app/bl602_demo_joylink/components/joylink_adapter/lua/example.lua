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

function stringToHexstring(str)
	local ret = ''
	for i=1, #str do
		ret = ret .. string.format("%02x", str:byte(i))
	end
	return ret
end

function decode(cmd)
	local tb
	if cjson == nil then	
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
	local bin
	if bizcode == 1002 then
		local json = decode(cmd)
		local streams = json["streams"]
		local tabstreams = getKVTable(streams, 'stream_id', 'current_value')

		bin = {0xbb, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,0xfa, 0x44}
		if (tabstreams["beep_switch"] == "0") then
			bin[2] = 3
		elseif (tabstreams["beep_switch"] == "1") then
			bin[2] = 2
		end

	elseif bizcode == 1004 then	--获取快照
		bin = {0xbb, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,0xfa, 0x44}
	else				--错误的code指令,返回获取快照
		bin = {0xbb, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,0xfa, 0x44}
	end

	local ret = tableTostring(bin)
	return 0, string.len(ret), ret
end

function pri2jds( bizcode, length, bin )
	--return err, jstr, bizcode
	local bin_cmd 	= {}
	local pwr
	local jdstr = ""
	
	bin_cmd = stringToTable(bin)
	
	for i=1, #bin_cmd do
		print(string.format("lua_script bin_cmd[%02d] %02x", i, bin_cmd[i]))
	end

	pwr  	= bin_cmd[1];
	jdstr 	= string.format('{"code":0,"streams":[{"current_value":%x,"stream_id":"switch"}],"msg":"done"}', pwr)

	return 0, jdstr, 102

end


