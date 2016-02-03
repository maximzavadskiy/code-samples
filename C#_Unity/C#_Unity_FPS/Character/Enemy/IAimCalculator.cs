using UnityEngine;
using System.Collections;
//abstract class for providing interface for calculation of aim for different weapons
public abstract class IAimCalculator : MonoBehaviour {
	
	abstract public Vector3 CalculateAim(Vector3 from, Vector3 to, float bulletSpeed);
}
