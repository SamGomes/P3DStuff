using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Door : MonoBehaviour {

    void OnTriggerEnter()
    {
       this.GetComponent<Animator>().SetBool("closeDoor", true);
    }
}
