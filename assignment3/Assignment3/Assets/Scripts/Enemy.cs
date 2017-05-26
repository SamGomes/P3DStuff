using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Enemy : MonoBehaviour {

    public GameObject player;
    public float firingDelay;
    private float lastShot;
    public int life;

    public void injure(int hp)
    {
        life -= hp;
    }

    // Use this for initialization
    void Start () {
        player = GameObject.Find("FPSController");
    }
	
	// Update is called once per frame
	void Update () {

        if(life <= 0)
        {
            this.gameObject.SetActive(false);
        }

        transform.rotation = Quaternion.LookRotation(transform.position - player.transform.position, Vector3.up);
        if ((Time.realtimeSinceStartup - lastShot) > firingDelay)
        {
            lastShot = Time.realtimeSinceStartup;
            this.gameObject.GetComponentInChildren<Gun>().fire();
        }
    }
}
