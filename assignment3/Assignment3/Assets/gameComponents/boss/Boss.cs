using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Boss : MonoBehaviour {

	// Use this for initialization
	void Start () {
        playSound();
	}
	
	// Update is called once per frame
	void Update () {
		
	}

    void playSound() {
        GetComponent<AudioSource>().Play();
    }

    void afterBossDeath() {

    }
}
