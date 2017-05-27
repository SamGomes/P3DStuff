using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Door : MonoBehaviour {

    void OnTriggerEnter(Collider col)
    {
        if (col.gameObject.GetComponent<Player>())
        {
            this.GetComponent<AudioSource>().Play();
            this.GetComponent<Animator>().SetBool("closeDoor", true);
        }
    }
}
