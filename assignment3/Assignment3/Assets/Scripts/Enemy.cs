using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Enemy : MonoBehaviour {

    public GameObject player;

	// Use this for initialization
	void Start () {

    }
	
	// Update is called once per frame
	void Update () {
        //Billboard effect always looks at the camera
        transform.LookAt(transform.position + player.transform.rotation * Vector3.forward,
            player.transform.rotation * Vector3.up);
    }
}
