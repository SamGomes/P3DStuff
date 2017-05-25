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
        transform.rotation = Quaternion.LookRotation(transform.position - player.transform.position, Vector3.up);
        if ((Time.realtimeSinceStartup - lastShot) > firingDelay)
        {
            lastShot = Time.realtimeSinceStartup;
            this.gameObject.GetComponentInChildren<Gun>().fire();
        }
    }
}
