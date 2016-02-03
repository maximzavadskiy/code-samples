using UnityEngine;
using System.Collections;

public class FaceThePlayerMotor : MonoBehaviour {
	
	public float rotationSpeed = 30f;
	
	GameObject player;
	
	void Start () {
		player = GameObject.FindGameObjectWithTag("Player");
	}
	
	void Update () {
		if(player) {
		    Vector3 targetPoint = player.transform.position;
            Quaternion targetRotation = Quaternion.LookRotation(targetPoint - transform.position, Vector3.up);
            transform.rotation = Quaternion.RotateTowards(transform.rotation, targetRotation, Time.deltaTime * rotationSpeed);    
		}
	}
}
