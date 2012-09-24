function GetStatus()
{
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
				},
				error : function() {
					alert("BAD");
				}
			}
		)
}

function SetPicture(BoardID, PictureIndex)
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