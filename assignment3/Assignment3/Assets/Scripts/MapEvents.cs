using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MapEvents : MonoBehaviour {
    public GameObject player;
    public GameObject bossPrefab;
    public bool spawnedBoss;

    public GameObject bossDoor;

    void Start()
    {
        spawnedBoss = false;
    }

    void Update()
    {
        if (!spawnedBoss && bossDoor.GetComponent<Door>().isClosed)
        {
            GameObject boss = Instantiate(bossPrefab);
            boss.transform.parent = GameObject.Find("LevelBoss").transform;
            spawnedBoss = true;
        }
    }

    void OnTriggerEnter(Collider col)
    {
        if (col.gameObject.GetComponent<Player>())
        {
            player.GetComponent<Player>().injure(100);
        }
    }
}
