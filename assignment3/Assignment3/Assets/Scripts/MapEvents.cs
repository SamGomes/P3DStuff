using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MapEvents : MonoBehaviour {
    public AudioClip playthroughMusicStart;
    public AudioClip playthroughMusicLoop;
    public AudioClip bossMusicStart;
    public AudioClip bossMusicLoop;
    public GameObject player;
    public GameObject bossPrefab;
    public bool spawnedBoss;

    public GameObject bossDoor;

    void Start()
    {
        StartCoroutine(playComplexMusic(playthroughMusicStart, playthroughMusicLoop));
        spawnedBoss = false;
    }

    void Update()
    {
        if (!spawnedBoss && bossDoor.GetComponent<Door>().isClosed)
        {
            GameObject boss = Instantiate(bossPrefab);
            boss.transform.parent = GameObject.Find("LevelBoss").transform;
            spawnedBoss = true;
            StartCoroutine(playComplexMusic(bossMusicStart, bossMusicLoop));
        }
    }

    void OnTriggerEnter(Collider col)
    {
        if (col.gameObject.GetComponent<Player>())
        {
            player.GetComponent<Player>().injure(100);
        }
    }

    private IEnumerator playComplexMusic(AudioClip start, AudioClip loop) {
        AudioSource player = GetComponent<AudioSource>();

        player.loop = false;
        player.clip = start;
        player.Play();
        yield return new WaitForSeconds(player.clip.length);
        player.clip = loop;
        player.loop = true;
        player.Play();
    }

    
}
