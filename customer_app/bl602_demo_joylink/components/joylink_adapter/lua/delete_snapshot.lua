function jds2pri(code, jds) 
	local error_code = 0
	local newJds = rmvSnapshot(jds)
	local cmd_length = #newJds
	return error_code, cmd_length, newJds
end

function pri2jds(code, length, bin) 
	local error_code = 0
	return error_code, bin, code
end

function rmvSnapshot(jds)
    local json = decode(jds)

    local streams = json["streams"]

    local retTable = {};

    retTable["streams"] = streams;
    return encode(retTable)
end

function decode(cmd)
    local tb = {}
    if cjson == nil then
        cjson = (require 'JSON')
        tb = cjson:decode(cmd)
        cjson = nil
    else
        tb = cjson.decode(cmd)
    end
    return tb
end

function encode(cmd)
    local tb = ""
    if cjson == nil then
        cjson = (require 'JSON')
        tb = cjson:encode(cmd)
        cjson = nil
    else
        tb = cjson.encode(cmd)
    end
    return tb
end