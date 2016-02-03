using UnityEngine;
using System.Collections;

public class LinearAimCalculator : IAimCalculator {
	
	override public Vector3 CalculateAim(Vector3 from, Vector3 to, float bulletSpeed){
		return to-from;	
	}
}
