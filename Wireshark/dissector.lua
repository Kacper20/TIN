asn_proto = Proto("admin-server-node","ASN Protocol")
-- create a function to dissect it


function asn_proto.dissector(buffer,pinfo,tree)
    pinfo.cols.protocol = "ASNPROTOCOL"
    local subtree = tree:add(asn_proto,buffer(),"ASN Protocol Data")
    local len = buffer:len()
    local temp = buffer:range(0,len)
    local temp1 = temp:string()
    local msg_type = string.sub(temp1,0,24)
    if msg_type == "{\"commandType\":\"startNew" then
	local t = string.sub(temp1,0,32)
	if t == "{\"commandType\":\"startNewProcessW" then
		pinfo.cols.info:set("Sending new proceess with schedule.")
	else 
		pinfo.cols.info:set("Sending new process to run.")
	end
    elseif msg_type == "{\"commandType\":\"launchPr" then
	pinfo.cols.info:set("Launching process.")
    elseif msg_type == "{\"commandType\":\"deletePr" then
	pinfo.cols.info:set("Deleting process.")
    end
    
end

tcp_table = DissectorTable.get("tcp.port")

for i=1500, 60000 do
tcp_table:add(i,asn_proto)
tcp_table:add(i,asn_proto)
tcp_table:add(i,asn_proto)
end

