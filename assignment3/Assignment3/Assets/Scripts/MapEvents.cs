using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MapEvents : MonoBehaviour {
    public GameObject player;
    void OnTriggerEnter(Collider col)
    {
        if (col.gameObject.GetComponent<Player>())
        {
            player.GetComponent<Player>().injure(100);
        }
    }
}
