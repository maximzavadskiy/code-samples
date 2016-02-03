using UnityEngine;
using System.Collections;

public class ProjectileAimCalculator : IAimCalculator {
	
	override public Vector3 CalculateAim(Vector3 from, Vector3 to, float bulletSpeed){
		float dist = (to-from).magnitude;
		float gravity = Physics.gravity.magnitude;
		//calculate the shoting angle using ballistic formula (source - wiki)
		float aimAngle = Mathf.Atan(
								(
									Mathf.Pow(bulletSpeed, 2) - 
									Mathf.Sqrt(
										Mathf.Pow(bulletSpeed, 4) - 
										Mathf.Pow(gravity, 2) * Mathf.Pow(dist, 2)
									)
								) / (gravity * dist)
							);
							
		if(float.IsNaN(aimAngle	)) aimAngle = Mathf.PI / 4f;
		
		Vector3 aimVector = to - from;
		aimVector = Quaternion.AngleAxis(aimAngle * Mathf.Rad2Deg, Vector3.Cross( aimVector, Vector3.up) ) * aimVector;
		
		return aimVector;
	}
}
