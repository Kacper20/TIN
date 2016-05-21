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

### Node - Server Communication

##### Sending process to node:
```
{
	“messageType” : “startNewProcess”;
	“processDetails” : {
	    "processID" : number;
		“content” : "echo "Hallo World""; // shell script
		"schedule" : ["start" : ""] //time when process should be run - format is hh:mm:ss.s
	}
}
```

##### Requesting statistics from specific run on node:
Requesting process statistic from runs is specified timeframe
```
{
    "messageType" : "requestStatistics";
    "specificData" : {
        "processID" : number;
        "timeFrame" : ["begin" : "", "end" : ""]  //specifying time frame - format YYYY-MM-DDThh:mm:ss.s
    }
}
```

##### Send requested data to server:
Respond to server request
```
{
    "messageType" : "sendStatistics";
    "specyficData" : ["timeFrame" : number, "runData" : ""]
}
```

##### Request deleting process on node:
```
{
    "messageType" : "deleteProcess";
    "processID" : number
}
```

##### Delete process on node:
```
{
    "messageType" : "deleteProcess";
    "processID" : number;
}
```

### Node - Admin Communication

##### Insert process Code:
```
{
    "messageType" : "insertCode";
    "processDetails" : {
        "processID" : number;
        "schedule" : ["start" : ""]; //time when process should be run - format hh:mm:ss.s
        "content" : "" //shell script
    }
}
```

##### Request statistics from process:
```
{
    "messageType" : "requestStats";
    "details" : {
        "processID" : number;
        "timeFrame" : ["begin" : number, "end" : number] //specifying timeframe - format YYYY-MM-DDThh:mm:ss.s
    }
}
```

##### Request system statistics:
```
{
    "messageType" : "systemStatistics"
}
```

##### Delete process:
```
{
    "messageType" : "deleteProcess";
    "processID" : number
}
```
