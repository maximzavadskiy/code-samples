'use strict';

var BreadCrumbs = function(url, separator) {
  this._separator = separator;
  this._crumbs = [];
    
  this.constructFromUrl(url);
}

// parses url and saves it to _crumbs -  label&path segment pairs
BreadCrumbs.prototype.constructFromUrl = function(url) {
  //extract path from url
  var matches = url.match(/^(\w+:\/\/)?[^:\/]+\/?([^\?#]*)/);
  if(matches === null) 
    return;
  var labels = matches[2].split('/');
  
  //assume the url is correct, so only assume "" possible as the last element of labels
  if(labels.length > 0 && labels[labels.length - 1] === "")
      labels.pop();
   
  if(labels.length > 0) {
     //normilize last segment in path
     //WARNING index. might be too greedy, also can not filter out all extensions
     var pathSegments = labels.slice();
     var lastSegmentFiltered = labels.pop().replace(/(^index\..*$)|(\.(html|htm|php|asp)$)/, "");
     //add back if it is not filtered out completely
     if(lastSegmentFiltered !== "")
       labels.push(lastSegmentFiltered);
       this._crumbs = labels.map(function(label, i){
         //store abstract pathSegment rather than taking care of rendering whole path with '/'
         return { 'str' : label, 'pathSegment' : pathSegments[i] };
     });  
  }
}

//prettifies and acronymize labels
BreadCrumbs.prototype.prettifyLabel = function(label) {
  var dropWords = ["the","of","in","from","by","with","and", "or", "for", "to", "at", "a"];
  var parts = label.split("-");
  var prettified = "" 
  //acronymize
  if(label.length > 30) {
    prettified =  parts.map(function(part) {
      if(dropWords.indexOf(part) === -1) {
        return part[0];
      }
    }).join("");
  //just get rid of "-"
  //WARNING may get rid of needed "-"
  } else {
    prettified  = parts.join(" ");
  }
 
  return prettified.toUpperCase()
}

//generate html representation
BreadCrumbs.prototype.toHTML = function() {
  //add home page to crumbs - it's a decorator, so it is not done in constructor
  var labelsPairs = [{str: "home", pathSegment: ""}].concat(this._crumbs);
  
  var labels = labelsPairs.map(function(x){return x.str});
  
  labels = labels.map(this.prettifyLabel);
  
  lastPath = "";
  var pathSegments = labelsPairs.map(function(x){
    lastPath += x.pathSegment + "/"; 
    return lastPath;
  });
  
  var labelsMarkup = labels.map(function(label,i) {
      if(i !== labels.length - 1) {
        return  '<a href="' + pathSegments[i] + '">' + label + '</a>';
      } else {
        return '<span class="active">' + label + '</span>';
      }
    }
  );
  
  return labelsMarkup.join(this._separator);
}

function generateBC(url, separator) {
  return new BreadCrumbs(url, separator).toHTML();
}
