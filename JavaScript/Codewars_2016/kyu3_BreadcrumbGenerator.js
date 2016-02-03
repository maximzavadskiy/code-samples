//My is based on computing distances between each stars separetely for catalog set and for observation set.
//Then p1 from catalog set (CS)  and p2 from observation set (OS)  are choosen in a such way, 
// that p1a, p1b are the points with the minimal distance from all pairs of points in OS and p2a, p2b the same way for CS
// If OS == CS, then either p1a == p2a or p1a == p2b. To check this (e.g. that p1a == p2a), the sorted distances from p1a to other points of CS must be all equal to sorted distances from p2a to other points of OS
//And matching points are also determined based on equality of distances
// This algorithm is theoretically only an heuristic, as exact angular positions on spheres are not compared. (E.g. there can be 2 points equally distanced from a given point (circle with center at a given point))
// However given sufficient camer resolution in real world absolutely exact distance for any 3 stars are unlikely (probably the probability of error of the camera resulting in the wrong match is more likely)
// However I did not verify the algorithm on real data, so feel free to critique it - it passed the tests though

function StarTracker(catalog) {
  this._catalog = catalog;
  //pregenerate distances pairs
  this._catalogDists = StarTracker.makeDistances(catalog);
}

StarTracker.prototype.matches = function(observations) {
  dists1 = this._catalogDists;
  dists2 = StarTracker.makeDistances(observations);
  
  //since distances are sorted in both arrays, then first 2 elements in dists1 and dists2 are the pairs that contain same stars
  //to find out which correcponds to which, try 2 possible combinations:
  return matchedPairs = StarTracker.makeMatchStarPairs(dists1[0].fromI,dists2[0].fromI, this._catalog, observations) || 
                        StarTracker.makeMatchStarPairs(dists1[0].fromI,dists2[1].fromI, this._catalog, observations);
}

//generates all distances array from the given points array, sorted by distance, stores original indexes
StarTracker.makeDistances = function(points) {
  var dists = []
  points.forEach( function(p1, i1) {
    points.forEach( function(p2, i2) {
      if(i1 !== i2) dists.push( {fromI: i1, toI: i2, dist: distance(p1,p2)});
    });
  });
  dists.sort(function(a,b) {return a.dist - b.dist});
  return dists;
}

//pairs up the stars from 2 sets, given the 2 stars that are considered to be the same, or returns [] if those 2 stars are not same
StarTracker.makeMatchStarPairs = function( i1, i2, points1, points2) {
  var dists1 = points1.map(function(x) {return {dist : distance(x, points1[i1]), p: x}}).sort(function(a,b){return a.dist - b.dist});
  var dists2 = points2.map(function(x) {return {dist : distance(x, points2[i2]), p: x}}).sort(function(a,b){return a.dist - b.dist});

  return dists1.reduce(function(pairs, p, i) {
    if(pairs !== null && floatEq(p.dist, dists2[i].dist)) {
      pairs.push([p.p, dists2[i].p])
      return pairs;
    } else {
      return null;
    }
  }, []);
}

//quadratic distance
function distance(p1, p2) {
  return p1.reduce(function(sum, __, i) { 
    return sum + Math.pow(p1[i] - p2[i], 2)
  }, 0);
}

//Compare 2 floats to be nearly equal, the delta is taken from looking at the example
function floatEq(f1, f2) {
 return Math.abs(f1 - f2) < Math.pow(10, -14);
}
