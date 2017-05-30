using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Boss : Enemy {

	// Use this for initialization
	void Start () {
        base.initialize();
        playSound();
	}
	
	// Update is called once per frame
	void Update () {
		
	}

    void playSound() {
        GetComponent<AudioSource>().Play();
    }

    public void afterBossDeath() {
        ScoreController scoreController = GameObject.Find("ScoreController").GetComponent<ScoreController>();
        scoreController.addScore("Boss Kill", 10000);
        int timeBonus = 240 - (int)Time.timeSinceLevelLoad;
        if (timeBonus > 0) {
            scoreController.addScore("Time x" + timeBonus, timeBonus * 250);
        }

        StartCoroutine(GameObject.Find("room").GetComponent<MapEvents>().endGame());
    }

    override public void injure(int hp, GunType gun, Collider collider)
    {
        if (this.isDead)
            return;

        base.injure(hp, gun, collider);

        if (isDead)
        {
            transform.GetChild(0).GetComponent<Animator>().SetBool("isDead", true);
            GetComponent<Animator>().speed = 0;
        }
        else {
            transform.GetChild(0).GetComponent<Animator>().SetTrigger("isHurt");
        }
    }
}
