using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Pickable : MonoBehaviour {
    public AudioClip pickUpSound;

	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
	}

    public void onPickup() {
        GetComponent<AudioSource>().clip = pickUpSound;
        GetComponent<AudioSource>().Play();
    }
}
