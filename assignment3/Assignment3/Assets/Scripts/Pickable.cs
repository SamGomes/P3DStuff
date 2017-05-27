using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Pickable : MonoBehaviour {
    public AudioClip pickUpSound;
    public bool picked;

    // Use this for initialization
    void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
        if (!picked)
            transform.Rotate(new Vector3(0, 0, 150) * Time.deltaTime);
    }

    public void onPickup() {
        GetComponent<AudioSource>().clip = pickUpSound;
        GetComponent<AudioSource>().Play();
    }
}
