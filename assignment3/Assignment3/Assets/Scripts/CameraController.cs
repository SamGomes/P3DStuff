using UnityEngine;
using System.Collections;

public class CameraController : MonoBehaviour {
    public GameObject player;
    private Vector3 offset;

	// Use this for initialization
	void Start () {
        Physics.gravity = new Vector3(0,-200.0f,0);
        offset = transform.position -  player.transform.position;
    }
	
	// Update is called once per frame
	void LateUpdate () {

        Vector3 forward = new Vector3(0, 0, 1);
        transform.rotation = player.transform.rotation;
        transform.position = player.transform.position + offset;

        
    }
}
