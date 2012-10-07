/*
	var returnvalue;
	$.ajax(
			{
				type : "GET",
				url : "http://localhost:8080",
				dataType : "jsonp",
				jsonp: "callback",
				success: function(data) {
					var index;
			        if(data != null)    {
			            for(index = 0 ; index < 4 ; index++)
			            {
			            	console.log(data[index].ID + ", " +  data[index].Top + ", " +  data[index].Right + ", " +  data[index].Bottom + ", " +  data[index].Left );
			        	}
			        }
			        returnvalue = data;
				},
				error : function() {
					alert("BAD");
				}
			}
		)
	return returnvalue;
*/


var SmartCubeCellStatus = [
[ 0,0,0,0],
[ 0,0,0,0],
[ 0,0,0,0],
[ 0,0,0,0]
]
/* = new Array(4);
for(var smartcubeindex = 0; smartcubeindex < 4 ; smartcubeindex++)
{
	SmartCubeCellStatus[smartcubeindex] = new Array(4);
}*/
function SmartCubeCheckCell()
{
	setTimeout("SmartCubeCheckCell()", 1000); //10000(10초간격으로 실행: 주기적)	
	$.ajax(
			{
				type : "GET",
				url : "http://localhost:8080",
				dataType : "jsonp",
				jsonp: "callback",
				success: function(data) {
					var index = 0;
			        if(data != null)    {
			            for(index = 0 ; index < 4 ; index++)
			            {
			            	//console.log(index + ": " +data[index].ID + ", " +  data[index].Top + ", " +  data[index].Right + ", " +  data[index].Bottom + ", " +  data[index].Left );
			        		if(data[index].Top != 0)
			        		{
			        			SmartCubeCellStatus[index][0] = data[index].Top - 1;
			        		}
			        		else
			        		{
								SmartCubeCellStatus[index][0] = 0xff;	
			        		}

							if(data[index].Right != 0)
			        		{
			        			SmartCubeCellStatus[index][1] = data[index].Right - 1;
			        		}
			        		else
			        		{
								SmartCubeCellStatus[index][1] = 0xff;
			        		}

			        		if(data[index].Bottom != 0)
			        		{
			        			SmartCubeCellStatus[index][2] = data[index].Bottom - 1;
			        		}
			        		else
			        		{
								SmartCubeCellStatus[index][2] = 0xff;
			        		}

			        		if(data[index].Left != 0)
			        		{
			        			SmartCubeCellStatus[index][3] = data[index].Left - 1;
			        		}
			        		else
			        		{
								SmartCubeCellStatus[index][3] = 0xff;
			        		}	
			        	}

			        }
			        
				},
				error : function() {
					alert("BAD");
				}
			}
		)
}
SmartCubeCheckCell();

function SmartCubeGetStatus()
{
	return SmartCubeCellStatus;
}

function SmartCubeSetPicture(BoardID, PictureIndex)
{
	var str = "BoardID=" + BoardID + "&PictureIndex=" + PictureIndex;
	$.ajax(
			{
				type : "POST",
				url : "http://localhost:8080",
				//dataType : "jsonp",
				//jsonp: "callback",
				data : str,
				success: function(data) {
					
				},
				error : function() {
					//alert("BAD");
				}
			}
		)
}