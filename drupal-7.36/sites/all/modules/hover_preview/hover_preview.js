
/*
 * Hover preview javascript
 *
 * Inspired by http://cssglobe.com/post/1695/easiest-tooltip-and-image-preview-using-jquery
 *   by Alen Grakalic (http://cssglobe.com)
 *
 */

Drupal.behaviors.HoverPreview = function (context) {
  /* CONFIG */
    
    yOffset = 10;
    xOffset = 30;
    docHeight = $(document).height();
		//get here because document height could change during DOM manipulation 
    // these 2 variable determine popup's distance from the cursor
    // you might want to adjust to get the right result
    
  /* END CONFIG */

  //determins the length of the title in pixels.
  String.prototype.visualLength = function()
  {
      var ruler = document.getElementById("ruler");
      ruler.innerHTML = this;
	    return ruler.offsetWidth;
  }  

  $("img.hover-preview").hover(function(e){

    this.t = this.title;

    //this.title = "";  
    var c = (this.t != "") ? "<br/>" + this.t : "";
    var preview_link = $('#' + this.id + '-url')[0]; //why [0] ?
    
    img_width = $(preview_link).width();
    img_height = $(preview_link).height();
    
    //Output of the preview element
    $("body").append("<span id='ruler'></span><p id='hover-preview'><img src='" + preview_link.src + "' alt='Loading Image Preview' />" + c + "</p>");
    $("#hover-preview")
      .css("top",(e.pageY - yOffset) + "px")
      .css("left",(e.pageX + xOffset) + "px")
      .fadeIn("fast");
    },
    
  function(){
   // this.title = this.t;  
    $("#ruler").remove();
    $("#hover-preview").remove();
    });   

  
  //keep track of mouse movement in an image and move preview element
  $("img.hover-preview").mousemove(function(e){
  
  var elementHeight = $("p#hover-preview").outerHeight(true);
  var elementWidth = $("p#hover-preview").outerWidth(true);
  var winHeight = $(window).height();
  var winWidth = $(window).width();
	var scrolledPixel = $(window).scrollTop();
  var scrolledPixelLeft = $(window).scrollLeft();

  //Check if item title is too long.
  var tlen = this.title;
	var len = tlen.visualLength();

  if(len > elementWidth){
    elementWidth = len;
  }
  //Checks if the bottom was hit.
  if( ((winHeight - e.pageY + 20 +  scrolledPixel) <= elementHeight) ) {
		   var yPosition = winHeight - elementHeight + scrolledPixel;
  }
	//Checks if the right side was hit.
  if( ((winWidth - e.pageX - xOffset + scrolledPixelLeft) <= elementWidth) ) {
	     var xPosition = winWidth - elementWidth + scrolledPixelLeft;
  }

  if (yPosition != null || xPosition != null){
    if (yPosition != null && xPosition == null){
      $("#hover-preview")
        .css("top",(yPosition + yOffset) + "px")
	      .css("left",(e.pageX + xOffset) + "px");
		}
    if (yPosition == null && xPosition != null){
      $("#hover-preview")
		    .css("top",(e.pageY - yOffset) + "px")
		    .css("left",(e.pageX - elementWidth - xOffset) + "px");
    }
    if (xPosition != null && yPosition != null){
      $("#hover-preview")
       .css("top",(yPosition + yOffset) + "px")
       .css("left",(e.pageX - elementWidth - xOffset) + "px");
    }
  } else {
    $("#hover-preview")
      .css("top",(e.pageY - yOffset) + "px")
      .css("left",(e.pageX + xOffset) + "px");
  }
  });  
};
