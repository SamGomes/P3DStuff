using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Enemy : MonoBehaviour {

    public GameObject player;
    public float firingDelay;
    private float lastShot;
    

    // Use this for initialization
    void Start () {

    }
	
	// Update is called once per frame
	void Update () {
        //Billboard effect always looks at the camera
        transform.LookAt(transform.position + player.transform.rotation * Vector3.forward,
            player.transform.rotation * Vector3.up);
        if((Time.realtimeSinceStartup - lastShot) > firingDelay)
        {
            lastShot = Time.realtimeSinceStartup;
            this.gameObject.GetComponentInChildren<Gun>().fire();
        }
    }
}
