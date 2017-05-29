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
        ScoreController scoreController = GameObject.Find("ScoreController").GetComponent<ScoreController>();
        scoreController.addScore("Boss Kill", 10000);
        int timeBonus = 240 - (int)Time.timeSinceLevelLoad;
        if (timeBonus > 0) {
            scoreController.addScore("Time x" + timeBonus, timeBonus * 250);
        }

        StartCoroutine(GameObject.Find("room").GetComponent<MapEvents>().endGame());
    }
}
