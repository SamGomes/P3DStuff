using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MapEvents : MonoBehaviour {
    public GameObject player;
    void OnTriggerEnter()
    {
        player.GetComponent<Player>().injure(100);
    }
}
