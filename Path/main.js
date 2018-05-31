var express = require('express');
var mysql = require('mysql');
var mustache = require('mustache');
var bodyParser = require('body-parser');
var fs = require('fs');
var app = express();
var urlencodedParser = bodyParser.urlencoded({ extended: true });

var con = mysql.createConnection({
  host: "localhost",
  user: "root",
  password: "12345",
  database: "mydb"
});


// app.use(function(req, res) {
// 	res.send('404:Page not found', 404);
// });


app.get('/', function(req,res) {
	con.query("SELECT nodeA node FROM networkpath group by nodeA", function (err, vertex, fields) {
 		if (err) throw err;

 		var dataToInsert =  {
 			nodeList: vertex
 		};

 		fs.readFile('mainPage.html', function(err, dataRead) {
 			var html = mustache.to_html(dataRead.toString(), dataToInsert);
 			res.send(html);
 			res.end();
 		});
  	}); 	
});

///Select Table
app.post('/search', urlencodedParser, function (req,res) {
	console.log(req.body);
	var startPoint = req.body.start_point;
	var destinationPoint = req.body.end_point;

	// con.connect(function(err) {
	//   	if (err) throw err;
    	con.query("SELECT * FROM networkpath", function(err, edge, fields) {
    		if (err) throw err;
	    	//console.log(vertex);
	    	//console.log(edge);

	    	// var startPoint = 'I';
	    	// var destinationPoint = 'A';
	    	var minDist = 0;
	    	//var pathNode = [];
		    var finalResult = DijkstraAlgorithm(edge, destinationPoint, minDist, startPoint);
		    var s = "Min Distance: " + finalResult[0] + " path: " + finalResult[1];
		    console.log(s);
		    res.send(s);
    	});
	// });
});

var server = app.listen(48763, "localhost", function () {
   var host = server.address().address;
   var port = server.address().port;

   console.log("Example app listening at http://%s:%s", host, port)
})

function DijkstraAlgorithm(edge, curNode, minDist, startPoint, pathNode)
{

	if (pathNode === undefined) {
		pathNode = [];
	}

	pathNode.push(curNode);

	// stop when reach startPoint
	if (curNode == startPoint) {
		return [0, curNode];
	}

	var tempNode = [];
	var tempDist = [];
	for (var i = 0; i < edge.length; i++) {
		if (curNode == edge[i].nodeB) {
			if (pathNode.indexOf(edge[i].nodeA) == -1) {
				tempNode.push(edge[i].nodeA);
				tempDist.push(edge[i].cost);
			}
		}
	}

	// if dont have any node connect, it will be end point, give large value
	if (tempNode.length == 0) {
		return [9999, curNode];
	}

	var distList = [];
	var pathList = [];
	for (var i = 0; i < tempDist.length; i++) {
		var resultByRecursion = DijkstraAlgorithm(edge, tempNode[i], minDist + tempDist[i], startPoint, pathNode.slice(0));
		var num = tempDist[i] + resultByRecursion[0];
		distList.push(num);
		pathList.push(resultByRecursion[1]);
	}

	var result = Math.min(...distList);
	path = pathList[distList.indexOf(result)] + curNode;
	return [result, path];
}






// backup
// function DijkstraAlgorithm(edge, curNode, minDist, startPoint, pathNode)
// {
// 	console.log("======================================================");
// 	console.log("Called function curNode: " + curNode);


// 	if (pathNode === undefined) {
// 		pathNode = [];
// 	}

// 	pathNode.push(curNode);

// 	// stop when reach startPoint
// 	if (curNode == startPoint) {
// 		console.log("reach start point");
// 		return 0;
// 	}

// 	var tempNode = [];
// 	var tempDist = [];
// 	for (var i = 0; i < edge.length; i++) {
// 		if (curNode == edge[i].nodeB) {
// 			if (pathNode.indexOf(edge[i].nodeA) == -1) {
// 				tempNode.push(edge[i].nodeA);
// 				tempDist.push(edge[i].cost);
// 			}
// 		}
// 	}

// 	console.log("curNode: " + curNode + " tempNode: " + tempNode + " tempDist: " + tempDist + " pathNode: " + pathNode);

// 	// if dont have any node connect, it will be end point, give large value
// 	if (tempNode.length == 0) {
// 		return 9999;
// 	}

// 	var distList = [];
// 	for (var i = 0; i < tempDist.length; i++) {
// 		var numByRecursion = DijkstraAlgorithm(edge, tempNode[i], minDist + tempDist[i], startPoint, pathNode.slice(0));
// 		var num = tempDist[i] + numByRecursion;
// 		console.log("curNode: " + curNode + " Should be: " + num + " dist: " + tempDist[i] + " by method: " + numByRecursion);
// 		distList.push(num);
// 		console.log("Goto node: " + tempNode[i] + " dist: " + tempDist[i] + " final: " + distList[i]);
// 	}

// 	console.log("Check min: " + distList);
// 	return Math.min(...distList);
// }
