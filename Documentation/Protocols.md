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
	“messageType” “startNewProcess”;
	“processDetails” : {
		“content” : "" // shell script
	}
}
```
