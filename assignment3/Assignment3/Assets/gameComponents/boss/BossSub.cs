using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BossSub : MonoBehaviour {

    public void playDeathSound() {
        transform.parent.GetComponent<Boss>().playDeathSound();
    }

    public void deathAnimation()
    {
        GetComponent<Animator>().enabled = false;
        transform.parent.GetComponent<Boss>().afterBossDeath();
    }
}
