## TIN - API Documentation

Communication will be based on exchange of JSON files between components.
Every JSON will have a common part, that says about its type. This is needed to properly dispatch messages.
This part looks as follows:
```
{
	messageType: “” //
}
```



### Node - Server Communication

##### Sending process to node:
```
{
	“messageType” : “startNewProcess”;
	“processDetails” : {
	    "processID" : number;
		“content” : ""; // shell script
		"schedule" : ["begin" : number, "end" : number] // schedule for process
	}
}
```

##### Requesting statistics from specific run on node:
```
{
    "messageType" : "requestStatistics";
    "specificData" : {
        "processID" : number;
        "timeFrame" : ["begin" : number, "end" : number]  //specifying time frame
    }
}
```

##### Send requested data to server:
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
        "schedule" : ["begin" : number, "end" : number];
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
        "timeFrame" : ["begin" : number, "end" : number]
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