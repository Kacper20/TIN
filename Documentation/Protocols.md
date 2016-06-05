## TIN - API Documentation

Communication will be based on exchange of JSON files between components.
Every JSON will have a common part, that says about its type. This is needed to properly dispatch messages.
This part looks as follows:
```
{
	messageType: “” //
}
```

### Message boundaries
Every message is preceded by number of bytes. This is needed by receiver of the message in order to properly read it.

### Failed response
Every response has it's failed form - because errors could in any of the requests.
It's format is as follows:
```
{
	“commandType” : “startNewProcess”;
	"errorMessage": "Error has occured..."
}
```
*commandType* - type of command that fail concerns



### Node - Server Communication

#### Sending process to node with schedule(multiple run):


##### Request
```
{
	“commandType” : “startNewProcessWithSchedule”;
	“processDetails” : {
	  "processIdentifier" : ""
		“content” : "echo"
		"schedules" : [3600, 4800]
	}
}
```
*schedules* - array of ints -  timestamps from 00:00 hour in seconds
*content* - content of a process to run

##### Response
```
{
	“responseType” : “scheduledProcessEnded”;
	“processDetails” : {
	  	processIdentifier" : ""
		"date" : "20-06-1994"
		"timestamp" : 3600
	}
}
```

This response is send to the server every time when scheduled run of a process ends.
After receiving this, server could ask about specific info about this run by making another request.

*process Identifier* - string, UUID, magic number given by server to properly recognize process. Node resends it in response
*date* - specifies date in which process was run. It's in format dd-mm-
*timestamp* - timestamp from 00:00 in a given day.


Explanation:
When server specifies that process should run at given timestamps, it'll be run every day from day of the request at given time. Later, server could ask for given process run. When process ends, only short information about ending is send(see Sending process to node with schedule response).



#### Sending process to node for one time run

Method used when server wants to run method just one time. In response all details about the run are included.
##### Request
```
{
	“commandType” : “startNewProcess”;
	“processDetails” : {
	    "processIdentifier" : number; //
		“content” : "echo "Hallo World""; // shell script
	}
}
```

##### Response
```
{
	“responseType” : “startNewProcess”;
	“processDetails” : {
	  processIdentifier" : ""
		"standardError" : ""
		"standardOutput" : ""
	}
}
```

*standardError* - std error of a process
*standardOutput* - std output of a process




#### Requestic specific run data

Method used when server wants to check details about scheduled run of a process.
##### Request
```
{
	“commandType” : “getRunData”;
	“processDetails” : {
	  "processIdentifier" : number; //
		"date" : "20-06-1994"
		"timestamp" : 3600
	}
}
```

##### Response
```
{
	“responseType” : “runData”;
	“processDetails” : {
	  processIdentifier" : ""
		"date" : "20-06-1994"
		"timestamp" : 3600
		"standardError" : ""
		"standardOutput" : ""
	}
}
```

#### Delete process
Deletes process from node, together with all of its scheduled runs(if there are any)
##### Request
```
{
	“commandType” : "deleteProcess";
	“processDetails” : {
	  "processIdentifier" : number; //
	}
}
```

##### Response
```
{
	“commandType” : “deleteProcess”;
	"status" : 1
	"message" :
	“processDetails” : {
		"processIdentifier" : number; //
	}
}
```

*status*  - 1 if OK, 0 if error occured. If 0 was returned - specific message is included.
*message* - error description
