asn_proto = Proto("admin-server-node","ASN Protocol")
-- create a function to dissect it


function asn_proto.dissector(buffer,pinfo,tree)
    pinfo.cols.protocol = "ASNPROTOCOL"
    local subtree = tree:add(asn_proto,buffer(),"ASN Protocol Data")
    local len = buffer:len()
    local temp = buffer:range(0,len)
    local temp1 = temp:string()

    t ,k = string.find(temp1, "\"commandType\":\"startNewProcess\"")
    if t ~= nil then 
		pinfo.cols.info:set("Sending new process to run. - command")
    end
    t = string.find(temp1, "\"commandType\":\"startNewProcessW")
    if t ~= nil then
	pinfo.cols.info:set("Sending process with schedule. - command")
    end
    t = string.find(temp1, "\"commandType\":\"deleteProcess")
    if t ~= nil then
	pinfo.cols.info:set("Deleting process. - command")
    end		
    t = string.find(temp1, "\"commandType\":\"getRunData")
    if t ~= nil then
	pinfo.cols.info:set("Requesting data. - commnd")
    end
    t = string.find(temp1, "\"commandType\":\"getStatistics")
    if t ~= nil then
	pinfo.cols.info:set("Reequesting process statistics. - command")
    end
    t = string.find(temp1, "\"commandType\":\"launchProcess")
    if t ~= nil then
	pinfo.cols.info:set("Launching process. - command")
    end
    t ,k = string.find(temp1, "\"responseType\":\"startNewProcess\"")
    if t ~= nil then 
		pinfo.cols.info:set("Sending new process to run. - response")
    end
    t = string.find(temp1, "\"responseType\":\"scheduledProcessEnded")
    if t ~= nil then
	pinfo.cols.info:set("Process with schedule ended. - response")
    end
    t = string.find(temp1, "\"responseType\":\"processDelete")
    if t ~= nil then
	pinfo.cols.info:set("Deleting process. - response")
    end		
    t = string.find(temp1, "\"responseType\":\"processStatistics")
    if t ~= nil then
	pinfo.cols.info:set("Requesting statistics. - response")
    end
    t = string.find(temp1, "\"responseType\":\"processLaunc")
    if t ~= nil then
	pinfo.cols.info:set("Launching process. - response")
    end
    
end

tcp_table = DissectorTable.get("tcp.port")

for i=1500, 60000 do
tcp_table:add(i,asn_proto)
end

