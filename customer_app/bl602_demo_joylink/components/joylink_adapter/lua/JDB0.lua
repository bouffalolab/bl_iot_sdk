-----------------M3微波炉转换脚本--------------------------------
function string.fromhex(str)
    return (str:gsub('..', function (cc)
        return string.char(tonumber(cc, 16))
    end))
end

function string.tohex(str)
    return (str:gsub('.', function (c)
        return string.format('%02X', string.byte(c))
    end))
end

function getbyte(str,byteindex)
	local b15 = string.sub(str, ( byteindex *2)+1, ((byteindex+1) *2))
	return b15
end

function subbyte(str,startbyteindex,endbyteindex)
	local b15 = string.sub(str, ( (startbyteindex-1) *2)+1, ( endbyteindex *2)+1   )  
	return b15
end

function arraytostring(tdlist, startIndex, endIndex)
	local res ="";
	local initIndex = 1
	if tdlist[0] ~=nil then
		initIndex = 0
	end
	for i=initIndex,#tdlist do
		res = res..string.char(tdlist[i])
	end
	res = string.tohex(res)
	return res;
end

function arraytostringinByte(tdlist)
   	local res ="";
	local initIndex = 1
	if tdlist[0] ~=nil then
		initIndex = 0
	end
	for i=initIndex,#tdlist do
		res = res..string.char(tdlist[i])
	end
	return res;
end

function stringtoByteArray(str)
	local byteArray  = {}
	local ret = str
	for i=1, #ret do
		byteArray[i] = tonumber(string.format("%02x", ret:byte(i)),16)
	end
	
	return byteArray
end

function showByteString(str1)
	local ret = str1
	local str = ''
	for i=1, #ret do
		str = str .. string.format("%02x", ret:byte(i))
	end
	return str
end


--指令转换成字节数组
function toArray(strCmd)
	local arrayResult = {}
	local strCmdLen = string.len(strCmd)
	local byteLen = strCmdLen/2
	local startIndex = 0
	while startIndex <= byteLen do
		arrayResult[startIndex+1]=tonumber(getbyte(strCmd,startIndex),16)
		startIndex=startIndex+1
	end
	return arrayResult,byteLen
end

function getKVTable(t,keyName,valueName)
	print(serialize(t))
	local kvTable = {}
	for i=1, #t do
			key = t[i][''..keyName]
			val = t[i][''..valueName]
			kvTable[''..key] = ''..val
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



----对象序列化方法----------
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

function divided(value,num)
	value = getNumber(value,10) 
	num = getNumber(num,10)
	local resultInt = (value//num)   
	local leftInt =  value%num 
	return resultInt,leftInt    
end

function getNumber(value,radix)
	if value == nil then
		return 60621174
	else
		local typeOfValue = type(value)
		if typeOfValue == 'string' then
			return tonumber(value,radix)
		elseif typeOfValue == 'number' then
			return value
		end
	end
end

function getString(value)
	if value == nil then
		return "60621174"
	else
		local typeOfValue = type(value)
		if typeOfValue == 'string' then
			return value
		elseif typeOfValue == 'number' then
			return ''..value
		end
	end
end

-------------------business-----------------
function getcommandfrompowermode(powerMode)
	local command = 0;										
	if powerMode=="0" then
		command=0x0A
	elseif  powerMode=="1" then
		command=0x08
	elseif  powerMode=="2" then
		command=0x05
	elseif  powerMode=="3" then
		command=0x03
	elseif  powerMode=="4" then
		command=0x01
	end
	return command
end

function getpowermodefromcommand(command)
	local powerMode = 9												
	if command=="0A" then
		powerMode = 0
	elseif command =="08" then
		powerMode = 1
	elseif command =="05" then
		powerMode = 2
	elseif command =="03" then
		powerMode = 3
	elseif command=="01" then
		powerMode = 4
	end
	return powerMode
end


function getcommandfromworkmode(workMode)
	local command = 0;										
	if workMode == "2" then
		command = 0x01
	elseif  workMode == "1" then
		command = 0x02
	elseif workMode == "3" then
		command = 0x04
	end
	
	return command
end

function getworkmodefromcommand(command)
	local workMode = 0												
	if command=="01" then
		workMode=2
    elseif command=="02" then
		workMode=1
	elseif command=="04" then
		workMode=3
	elseif command=="08" then
		workMode=4
	end
	return workMode
end



--将json解释成十六进制指令
function convert_to_private(t)

	tdlist = {
		 [0] = 0xAA,       --header
		 [1] = 0x17,       --len
		 [2] = 0xB0,       --B0
		
		 [3] = 0x00,       --00
		 [4] = 0x00,       --00
		 [5] = 0x00,       --00
		 [6] = 0x00,	   --00
		 [7] = 0x00,       --00
		 [8] = 0x00,       --00
		 	
		 [9] = 0x02,       --msg type 02
		
		 [10] = 0x00,	   --status 
		 [11] = 0x00,      --workmode
		
		 [12] = 0x00,      --time_hour
		 [13] = 0x00,	   --time_minute
		
		 [14] = 0x00,      --wordmode arg1
		 [15] = 0x00,      --is multiSeg command 
		
		 [16] = 0x00,      --00
		 [17] = 0x00,      --00
		 [18] = 0x00,      --00
		 [19] = 0x00,	   --00
		
		 [20] = 0x00,      --00 id1
		 [21] = 0x00,      --00 id2
		 [22] = 0x00,      --00 id3
		
		 [23] = 0x00,      --checksum
		 
		 }

	local msgLenByteNumber = 23
	if t['KG_Cancel']~=nil then
		if t['KG_Cancel']['value'] == "1" then 
			tdlist[10] = 0x01
		end
	elseif t['KG_Start']~=nil then
		if t['KG_Start']['value'] == "0" then 
			tdlist[10] = 0x03
		elseif t['KG_Start']['value'] == "1" then 
			tdlist[10] = 0x02
		end
	elseif t['KG_Lock']~=nil then
		if t['KG_Lock']['value'] == "0" then 
			tdlist[10] = 0x01
		elseif t['KG_Lock']['value'] == "1" then 
			tdlist[10] = 0x05
		end
	elseif t['Status_Update']~=nil then
		if t['Status_Update']['value'] == "1" then 
			tdlist[9] = 0x03
		elseif t['Status_Update']['value'] == "0" then
				return "DDFF18AA17B0000000000000030000000000000000000000000036";
		end
	elseif t['WF'] ~= nil then
		if t['WF']['extra'] ~= nil then
					if t['WF']['extra']['Type'] == "0" then 
						if t['WF']['extra']['WF_ID'] ~= nil then 
							if t['WF']['extra']['PreSet'] ~= nil then
									local workMode = t['WF']['extra']['WF_ID']
									local powerMode = t['WF']['extra']['PreSet']['PowerMode']
									local workTime =  t['WF']['extra']['PreSet']['WorkTime']
									local weight =  t['WF']['extra']['PreSet']['Weight']
									
									local min_time =  t['WF']['extra']['PreSet']['Min']
									local sec_time =  t['WF']['extra']['PreSet']['Sec']
									if workMode == "2" then
										tdlist[11] = 0x01
									elseif  workMode == "1" then
										tdlist[11] = 0x02
									elseif workMode == "3" then
										tdlist[11] = 0x04
									end
									
									if workMode == "2" or workMode=="1" then
										local workTimeNMinute,workTimeNSecond = divided(workTime,60) 
										tdlist[12]=workTimeNMinute		
										tdlist[13]=workTimeNSecond
										
										if  workMode == "2"  then
											tdlist[14]=getcommandfrompowermode(powerMode)
										end
										
										if workMode =="1" then
											tdlist[14]=0x01
										end
					
									elseif workMode == "3" then
										--local weightLen =  string.len(weight)-2;
										--weight = string.sub(weight,1,weightLen)
										local weightN = tonumber(weight)/100
										tdlist[15] = weightN
									end
									
									tdlist[10]=0x02  
							end
						end
					elseif t['WF']['extra']['Type'] == "1" then
						local cloundMenuId = t['WF']['extra']['WF_ID']
						local totalStep = t['WF']['extra']['StepNum']
						
						local totalStepN = tonumber(totalStep)
						if totalStepN > 0 then
							local b16 = totalStep.."1"
							tdlist[16]=tonumber(b16,16)				
							local cloundMenuIdNHH, cloundMenuIdNHHLeft = divided(cloundMenuId,(16^4)) 				
							local cloundMenuIdNH,cloundMenuIdNL = divided(cloundMenuIdNHHLeft,(16^2))  
							tdlist[20] = cloundMenuIdNHH
							tdlist[21] = cloundMenuIdNH
							tdlist[22] = cloundMenuIdNL				
							local stepDetail = t['WF']['extra']['Steps'][1]['Action']
									
							local nextSegStartMode = stepDetail['WorkStatus']
							local nextSegStartModeN = tonumber(nextSegStartMode)
									
							local workMode = stepDetail['WorkMode']
							tdlist[11]= getcommandfromworkmode(workMode)
							
							if workMode=="1" or workMode=="2" then
								local workTime = stepDetail['WorkTime']															
								local workTimeNMinute, workTimeNSecond = divided(workTime,60)								
								tdlist[12]= workTimeNMinute		
								tdlist[13]= workTimeNSecond	
								
								if workMode=="2" then
									local powerMode = stepDetail['PowerMode']
									tdlist[14] = getcommandfrompowermode(powerMode) 
								end
								
								if workMode == "1" then
									tdlist[14] = 0x01
								end
							elseif workMode=="3"   then
								local weight = stepDetail['Weight']
								local weightN = tonumber(weight)
								local weightN100 = weightN/100
								tdlist[15] = weightN100
							end	
							
							tdlist[10] = 0x02
							tdlist[19] = nextSegStartModeN
							
							
							local mutiSegNextIndex = 23
							if totalStepN > 1 then
								for i=2,totalStepN do 
									local stepDetail = t['WF']['extra']['Steps'][i]['Action']
									
									local nextSegStartMode = stepDetail['WorkStatus']
									local nextSegStartModeN = tonumber(nextSegStartMode)
											
									local workMode = stepDetail['WorkMode']
									tdlist[mutiSegNextIndex]= getcommandfromworkmode(workMode)
									mutiSegNextIndex = mutiSegNextIndex+1
									
									if workMode=="1" or workMode=="2" then
										local workTime = stepDetail['WorkTime']
										local workTimeN = tonumber(workTime);							
										local workTimeNMinute, workTimeNSecond = divided(workTime,60)									
										tdlist[mutiSegNextIndex]= workTimeNMinute	
										mutiSegNextIndex = mutiSegNextIndex+1	
										tdlist[mutiSegNextIndex]= workTimeNSecond	
										mutiSegNextIndex = mutiSegNextIndex+1
										
										if workMode=="2" then
											local powerMode = stepDetail['PowerMode']
											tdlist[mutiSegNextIndex] = getcommandfrompowermode(powerMode)
											mutiSegNextIndex = mutiSegNextIndex+1
											tdlist[mutiSegNextIndex] =0
											mutiSegNextIndex = mutiSegNextIndex+1 
										end
										if workMode=="1" then
											tdlist[mutiSegNextIndex] =0x01
											mutiSegNextIndex = mutiSegNextIndex+1
											tdlist[mutiSegNextIndex] =0
											mutiSegNextIndex = mutiSegNextIndex+1
											
										end
									elseif workMode=="3"   then
										tdlist[mutiSegNextIndex] =0
										mutiSegNextIndex = mutiSegNextIndex+1
										tdlist[mutiSegNextIndex] =0
										mutiSegNextIndex = mutiSegNextIndex+1
										tdlist[mutiSegNextIndex] =0
										mutiSegNextIndex = mutiSegNextIndex+1
										
										local weight = stepDetail['Weight']
										local weightN = tonumber(weight)
										local weightN100 = weightN/100
										
										tdlist[mutiSegNextIndex] = weightN100
										mutiSegNextIndex = mutiSegNextIndex+1
									end	
									tdlist[mutiSegNextIndex] = nextSegStartModeN
									mutiSegNextIndex= mutiSegNextIndex+1
								end
							end
							
							msgLenByteNumber = mutiSegNextIndex
							tdlist[1] = msgLenByteNumber
							
						end
					end
		end
	end

	--CRC8 	
	local crc = 0;
	for i=1, (msgLenByteNumber-1) do
	  crc = crc+tdlist[i];
	end
	crc=~(crc);
	crc=(crc&0x000000FF);
	crc=crc+1;
	tdlist[msgLenByteNumber] = crc;

	local res = arraytostring(tdlist,0,msgLenByteNumber)
	return res
end


--将十六进制指令解释成json
function convert_from_private(s)
	local str = s
	
	local result = {
		KG_Start = { value = '-1', when = ''},
		KG_Cancel = { value = '-1', when = ''},
		KG_Lock = { value = '0', when = ''},
		WorkStatus = { value = '0', when = ''},
		WorkMode = { value = '-1', when = ''},  
		Weight = { value = '0', when = ''},
		WorkTime = { value = '-1', when = ''},
		PowerMode  = { value = '-1', when = ''},  
		WF_CurrentStep = { value = '0', when = ''},
		WF_TimeLeft = { value = '0', when = ''},
		EC = { value = '0', when = ''},
		WF = { 
				value = '1', 
				when = '',
				extra = {
					WF_ID = '0',
					StepNum = '0',
					TimeTotal = '0',
					Type = '0'
				}
		}
	}
	
	local b9Temp = getbyte(str,9)
	local strLen = string.len(str)
	if strLen > (28*2) then
		if strLen==(28*2*2) and ( b9Temp == "02"  or b9Temp=="04" ) then
			str = subbyte(str,29,56)
		end
	end
	--[[
	local b4 = getbyte(str,4)
	if b4 ~= 'EE' then
		return nil
	end
	]]--
	
	local b10 = getbyte(str,10) 
	local b10N = tonumber(b10,16)
	local b10NH,b10NL = divided(b10,16)	
	--b10NH = tonumber(''..b10NH)

	if b10NH > 7 then
		result['EC']['value']='1';
		b10='0'..b10NL
	end
	
    local b16 = getbyte(str,16)  
	if str=="0808080808080808" then
		result['EC']['value']= "0";
	elseif b16~="00" then
		if b16 == "01" then
			result['EC']['value']= '1'
		elseif b16 == "02" then
			result['EC']['value']= '2'
		end
	end
	
	
	
	
	local workStatus = 0
	if b10=="01"  or b10=="07" then  
		workStatus = 0
	elseif b10=="02" then  
	    workStatus = 1  	
	elseif b10=="03" or b10=="09" then 
	    workStatus = 2
	elseif b10=="05" then 
	    workStatus = 3
	elseif b10=="66" then 
	    workStatus = 4
	elseif b10=="04" then 
	    workStatus = 5
	end
	
	local workMode = 9
	if workStatus == 1 or workStatus == 2 or workStatus==4 or workStatus==5 then
		local b11 = getbyte(str,11)
		workMode = getworkmodefromcommand(b11);
		
		if workMode == 1 or workMode == 2 or workMode == 3 or workMode==4 then
			local b12 = tonumber(getbyte(str,12), 16)
		    local b13 = tonumber(getbyte(str,13), 16)
		    local workTime = (b12*60) + b13
			
			result['WF_TimeLeft'] = {value = tostring(workTime), when=''}

			local powerMode = 0
			if workMode ==2 then 
				local b24 = getbyte(str,24)
				powerMode = getpowermodefromcommand(b24)
				result['PowerMode']['value'] =  tostring(powerMode)
			end
			
			if workMode ==4 then 
				result['PowerMode']['value'] =  '0'
			end
			
			if workMode == 3 then 
				local weight = 0
				local b25 = getbyte(str,25)
				weight = b25
				
				local weightN100 = tonumber(weight,16)*100
				result['Weight']['value'] =  tostring(weightN100)
			end
			
			result['WorkMode']['value'] =  tostring(workMode)
			result['WF']['extra']['WF_ID'] = tostring(workMode)
		
		end
		
		local b20 = getbyte(str,20)
		local b21 = getbyte(str,21)
		local b22 = getbyte(str,22)
		local b23 = getbyte(str,23)
		local cloundMenuId = tonumber(b21,16)*(16^4)+ tonumber(b22,16)*(16^2)+ tonumber(b23,16);
		
		local b20N = tonumber(b20,16);
		local totalStep,currentStep = divided(b20N,16)		
		
		if cloundMenuId ~= 0 then
			result['WF']['extra']['WF_ID'] = tostring(cloundMenuId)
			result['WF']['extra']['Type'] = "1"
			result['WF_CurrentStep']['value'] = tostring(currentStep)
			result['WF']['extra']['StepNum']  = tostring(totalStep)			
		end
	end
	
	 
	result['WorkStatus'] = {value = tostring(workStatus), when=''}
	return result

end

function is_increment()
	return true;                   
end

--查询指令
function private_cmd_query(t)
   local restring="AA17B0000000000000030000000000000000000000000036"
   return restring
end


--print(control('1','1','61',''))
function control(workMode,powerMode,workTime,weight,min_time,sec_time)
	local t = { WF = { extra = {
			        Type = '0',
		            WF_ID = '0',
				    PreSet = { PowerMode=nil,WorkTime=nil,Weight=nil,Min=min_time,Sec=sec_time}
		    } 		
		}	
	}
	t['WF']['extra']['Type'] = '0'
	if workMode== '1' then
		workMode = '2'
	elseif workMode == '2' then
		workMode = '1'
	end
	t['WF']['extra']['WF_ID'] = workMode
	t['WF']['extra']['PreSet'] =  {
		['PowerMode'] = powerMode,
		['WorkTime'] = workTime,
		['Weight'] = weight,
		['Min']=min_time,
		['Sec']=sec_time
	}           		
	return convert_to_private(t)
end


--多段工作
function cloundControl(MenuId, StepNum, Steps)
	local t = { WF = { extra = {
			    Type = nil,
				StepNum = nil,
		        WF_ID = nil,
				Steps = {  
							{ Action = { WorkStatus = nil, WorkMode = nil, PowerMode = nil,WorkTime = nil,Weight = nil} },
							{ Action = { WorkStatus = nil, WorkMode = nil, PowerMode = nil,WorkTime = nil,Weight = nil} }
						}
		    } 		
		}	
	}
	t['WF']['extra']['Type'] = '1'
	t['WF']['extra']['WF_ID'] = MenuId
	t['WF']['extra']['StepNum'] = StepNum
	t['WF']['extra']['Steps'] = Steps       		
	return convert_to_private(t)
end

--暂停
function pause()
	local t = {
	    KG_Start = {
            value = '0'		
		} 
	}
	local res = convert_to_private(t)
	return res
end

--继续
function continue()
	local t = {	    
	    KG_Start = {
            value = '1'		
		} 
	}
	local res = convert_to_private(t)
	return res
end

--取消
function cancel()
	local t = {
	    KG_Cancel = {
		    value = '1'
		} 
	}
	local res = convert_to_private(t)
	return res
end

--童锁
function lock()
	local t = {
        KG_Lock = {
		    value = '1'
		}	
	}
	local res = convert_to_private(t)
	return res
end

--解锁
function unlock()
	local t = {
	   KG_Lock = {
	       value = '0'
	   }
	}
	local res = convert_to_private(t)
	return res
end

--查询
function query()
	local res = private_cmd_query(t)
	return res 
end

function decodeStatus(r)
	if r==nil then
		return nil
	end
	local result = {
		Error='0',
		Lock='0',
		Type='-1',
		WorkStatus = r.WorkStatus.value,--0待机 1工作中 2暂停中 3童锁锁定 4完成   
		WorkMode='-1',
		PowerMode='-1',
		Weight='-1',
		TimeLeft='-1',
		StepNum='-1',
		CurrentStep=nil,
		MenuId = nil
	}
	
	if r.EC~=nil and r.EC.value=='1' then
		result.Error = '1'
		return result
	end
	
	if r.Lock~=nil and r.Lock.value=='1' then
		result.Lock = '1'
		return result
	end
	
	if r.WF.extra~=nil and r.WF.extra.Type=='0' then
		result.Type='0'
		result.WorkStatus = r.WorkStatus.value
		result.WorkMode=r.WorkMode.value
		result.PowerMode=r.PowerMode.value
		result.Weight=r.Weight.value
		result.TimeLeft=r.WF_TimeLeft.value
		return result
	elseif  r.WF.extra~=nil and r.WF.extra.Type=='1' then
		result.Type='1'
		result.WorkStatus = r.WorkStatus.value
		result.WorkMode=r.WorkMode.value
		result.PowerMode=r.PowerMode.value
		result.Weight=r.Weight.value
		result.TimeLeft=r.WF_TimeLeft.value
		result.StepNum=r.WF.extra.StepNum
		result.CurrentStep=r.WF_CurrentStep.value
		result.MenuId=r.WF.extra.WF_ID
		return result
	end
	return result
end
	

function uploadStatus(strCmd)
	return decodeStatus(convert_from_private(strCmd)) 
end

--------------------------------京东分隔线--------------------------------------------------------------
function getJD_KVTable(t)
	return getKVTable(t,'stream_id','current_value')
end

function makeJD_KVArray(t)
	return makeKVArray(t,'stream_id','current_value')
end

function decode(cmd, model) 
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


function jds2pri(code,cmd,model)
	print("翻译器收到的指令类型为"..code)
	
	local strCmd = ""
	if code==1002 then
		print("翻译器收到的json指令为"..cmd)
		local t = decode(cmd, model)
		local kv = getJD_KVTable(t.streams)

		if kv.switch == '1' then
			strCmd = cancel();
		elseif	kv.state=='1'	then
			strCmd = continue();
		elseif	kv.state=='2'	then
			strCmd = pause()
		elseif	kv.lock=='1'	then
			strCmd = lock();
		elseif	kv.lock=='0'	then
			strCmd = unlock();	
		elseif	kv.switch=='0'	then
			local workTime = nil
			if kv.min_time ~= nil and kv.sec_time ~= nil then
				workTime = tonumber(kv.min_time)*60 + tonumber(kv.sec_time)
			end

			strCmd = control(kv.mode,kv.power,workTime,kv.weight,kv.min_time,kv.sec_time)	
		end
		
		
	elseif code==1004 then
		strCmd = query()
	elseif code==1050 then
		print("翻译器收到的json指令为"..cmd)
		local t = decode(cmd, model)
		local i = 1
		local StepNum = #t['cmd']['subTask']
		local Steps = {}
		local MenuId = t['cmd']['task_id']
		while i <= StepNum  do
			local step = getJD_KVTable(t['cmd']['subTask'][i]['streams']) 
			--mode power min_time sec_time start_type weight
			local workMode = ''..step.mode     -- 1 微波 2 烧烤 3 解冻
			if workMode== '1' then
				workMode = '2'
			elseif workMode == '2' then
				workMode = '1'
			end
			local workTime = tonumber(''..step.min_time) *60 + tonumber(''..step.sec_time)
			
			local powerMode = ''..step.power 
			
			local weight = ''..step.weight
			local workStatus = ''..step.start_type
			if workStatus == '2' then
				workStatus = '1'
			end
			
			Steps[i]['Action'] = {
				 WorkStatus = workStatus, WorkMode = workMode, PowerMode = powerMode,WorkTime = workTime,Weight = weight
			}
		end
		strCmd = cloundControl(MenuId,StepNum,Steps)
	end
	
	if strCmd~="" then 
		print("翻译器将json指令理解为:"..strCmd)
		local byteArray,byteArrayLen = toArray(strCmd)
		return 0,byteArrayLen,arraytostringinByte(byteArray)
	else
		print("翻译器无法识别此json指令:"..cmd)
		return 0,0,serialize(kv)
	end

end

function pri2jds( code, length, bin, model )
	local byteArray = stringtoByteArray(bin)
	
	local strCmd = arraytostring(byteArray,0,#byteArray)
	print("翻译器收到的机器码为:"..strCmd)
	local resultCode = 0;
	local b9 = getbyte(strCmd,9)
	if b9=='02' then
		resultCode = 102
	elseif b9=='03' then
		resultCode = 104
	else
		resultCode = 104
	end
	
	local status = uploadStatus(strCmd)
	if status == nil then
		return nil
	end
	--cloudy_menu info lock min_dctime mode power sec_dctime state step  total_step weight switch
	local result = {
		info=status.Error,
		lock=status.Lock,
		switch = '0',
		cloudy_menu='0',
		state=nil,
		mode = nil,
		power=''..status.PowerMode,
		min_dctime=nil,
		sec_dctime=nil,
		weight=''..status.Weight,
		total_step = status.StepNum,
		step=status.CurrentStep,
		menu_id = status.MenuId 
	}
	
	if status.WorkStatus == '0' then
		result.switch = '1'
		result.state = '0'
	elseif status.WorkStatus == '1' then
		result.state = '1'
	elseif status.WorkStatus == '2' then
		result.state = '2'
	elseif status.WorkStatus == '3' then
		result.lock = '1'
	elseif status.WorkStatus == '4' then
		result.state = '3'
	elseif status.WorkStatus == '5' then
		result.state = '4'
	end
	
	if status.Type == '1' then
		result.cloudy_menu = '1'
	end
	
	if status.WorkMode == '1' then
		result.mode = '2'
	elseif status.WorkMode == '2' then
		result.mode = '1'
	elseif status.WorkMode == '3' then
		result.mode = '3'
	end
	
	local leftTimeMin,lettTimeSec = divided(status.TimeLeft,60)	
	result.min_dctime = ''..leftTimeMin
	result.sec_dctime = ''..lettTimeSec
	result = makeJD_KVArray(result)
	result = serializeArray(result)
	
	local resultStr = '{"code":0,"streams":'..result..'}'
	print("翻译器将收到的机器码翻译为:["..resultCode..']类型请求'..resultStr)
	
	return 0, resultStr, resultCode
end

print("Load OK")

