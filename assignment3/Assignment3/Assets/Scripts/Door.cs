using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Door : MonoBehaviour {
    public bool isSecretDoor;
    public bool isClosed = false;

    void OnTriggerEnter(Collider col)
    {
        if (col.gameObject.GetComponent<Player>() && !isClosed)
        {
            isClosed = true;
            if (isSecretDoor) {
                GameObject.Find("ScoreController").GetComponent<ScoreController>().addScore("Secret!!!", 5000);
            }
            this.GetComponent<AudioSource>().Play();
            this.GetComponent<Animator>().SetBool("closeDoor", true);
        }
    }
}
