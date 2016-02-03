using UnityEngine;
using System.Collections;

public class EnemyBarracks : MonoBehaviour {
	
	public GameObject[] enemies;
	
	public float minDistSpawn = 2f;
	public float maxDistSpawn = 5f;
	
	public float spawnPeriod = 3f;
	
	public float spawnHeight = 0.5f;
	
	public float spawnCollisionCheckRadius = 1f;
	public LayerMask checkSpawnCollisionForLayer;
	
	
	float lastSpawnTime = 0f;
	
	GameObject player;
	
	void Start () {
		player = GameObject.FindGameObjectWithTag("Player");
		//to spawn Immediately for first time
		lastSpawnTime = - spawnPeriod; 
	}
	
	
	void Update () {
		if(Time.time > lastSpawnTime + spawnPeriod) {
			//randomly select angle to spawn, related to forward vector, and distance to spawn
			float spawnVectorAngle = Random.Range(0f, 360f);
			float spawnVectorDistance = Random.Range(minDistSpawn, maxDistSpawn);
			
			Quaternion spawnVectorRotation = Quaternion.AngleAxis(spawnVectorAngle, Vector3.up);
			Vector3 spawnVector = spawnVectorRotation * transform.forward * spawnVectorDistance;
			
			Vector3 spawnPosition = transform.position + spawnVector;
			//adjust spawn height
			spawnPosition.y = spawnHeight; 
			
			//if there is smth on the spawn position, try next frame again
			if(Physics.OverlapSphere(spawnPosition, spawnCollisionCheckRadius, checkSpawnCollisionForLayer).Length == 0) {			
				GameObject enemy = (GameObject) GameObject.Instantiate(enemies[Random.Range(0, enemies.Length)], spawnPosition, spawnVectorRotation);
				//rotate towards the player
				if(player) enemy.transform.LookAt(player.transform.position);
				
				lastSpawnTime = Time.time;
			}
		}
	}
}
