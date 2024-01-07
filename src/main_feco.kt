import java.io.BufferedReader
import java.io.File

data class Interval(val start: Long, val len: Long)

data class MyTreeEntry(var dest: Long = 0, var src: Long = 0, var len: Long = 0)

class MyTreeMap {
    var left: MyTreeMap? = null
    var entry: MyTreeEntry = MyTreeEntry(0, 0, 0)
    var right: MyTreeMap? = null
    private var elements: Int = 0

    fun insert(num: MyTreeEntry) {
        if (elements == 0) {
            entry = num
        } else {
            recurInsert(this, num)
        }
        elements++
    }

    fun addInterval(intervals: MutableList<Interval>, seed: Interval) {
        recurGetIntervals(this, intervals, seed)
    }

    fun getAllInterval(seeds: List<Interval>): List<Interval> {
        return seeds.flatMap { seed ->
            mutableListOf<Interval>().apply { addInterval(this, seed) }
        }
    }

    fun read(line: String) {
        val parts = line.split(" ")
        if (parts.size == 3) {
            val localEntry = MyTreeEntry(parts[0].toLong(), parts[1].toLong(), parts[2].toLong())
            insert(localEntry)
        }
    }

    private fun recurInsert(root: MyTreeMap?, entry: MyTreeEntry): MyTreeMap {
        if(root == null){
            val neue = MyTreeMap()
            neue.insert(entry)
           return neue
        }
        if (entry.src < root.entry.src) {
            root.left = recurInsert(root.left, entry)
        } else if (entry.src > root.entry.src) {
            root.right = recurInsert(root.right, entry)
        } else {
            throw IllegalArgumentException("Duplicate entry")
        }
        return root
    }

    private fun recurGetIntervals(root: MyTreeMap?, intervals: MutableList<Interval>, seed: Interval) {
        if (root == null) {
            intervals.add(seed)
            return
        }

        val entry = root.entry
        val end = seed.start + seed.len
        val entryEnd = entry.src + entry.len

        if (seed.start < entry.src) {
            if (end < entry.src) {
                recurGetIntervals(root->left, intervals, seed);
                return;
            }
            if (end <= entryEnd) {
                recurGetIntervals(root->left, intervals,
                {seed.start, entry.src - seed.start});
                // add seed entry.dest : entry.dest + seed_len
                intervals.push_back({entry.dest, end - entry.src});
                return;
            }
            // seed.start + seed.len >= entry.src + entry.len
            recurGetIntervals(root->left, intervals,
            {seed.start, entry.src - seed.start});
            intervals.push_back({entry.dest, entry.len});
            recurGetIntervals(
                root->right, intervals,
            {entryEnd, seed.len - (entry.src - seed.start) - entry.len});
            return;
        }
        if (seed.start <= entryEnd) {
            const uint64_t start_offset = seed.start - entry.src;
            if (end <= entryEnd) {
                intervals.push_back({entry.dest + start_offset, seed.len});
                return;
            }
            // end > entryEnd
            intervals.push_back({entry.dest + start_offset, entry.len - start_offset});
            recurGetIntervals(root->right, intervals,
            {entryEnd, seed.len - (entry.len - start_offset)});
            return;
        }
        // seed_start > entryEnd
        recurGetIntervals(root->right, intervals, seed);
    }
}

class MyMap {
    private val map = MyTreeMap()

    fun read(reader: BufferedReader) {
        reader.readLine()
        var line: String? = reader.readLine()
        while(line?.isNotEmpty() == true){
            map.read(line)
            line = reader.readLine()
        }
    }

    fun getIntervals(seed: List<Interval>): List<Interval> {
        val kalap = map.getAllInterval(seed)
        return kalap
    }
}

class MyMapList {
    private val maps = Array(7) { MyMap() }

    fun read(file: BufferedReader) {
        maps.forEach {
            it.read(file)
        }
    }

    fun findAllLocations(seeds: List<Interval>): List<Interval> {
        var intervals = maps[0].getIntervals(seeds)
        for (i in 1 until maps.size) {
            intervals = maps[i].getIntervals(intervals)
        }
        return intervals
    }

    fun test(seeds: List<Interval>) {
        val intervals = maps[0].getIntervals(seeds)
        intervals.forEach { println(it) }
    }
}

fun findLowestSeed(seeds: List<Interval>, list: MyMapList): Long {
    val locations = list.findAllLocations(seeds)
    return locations.minOf { it.start }
}

fun main() {
    val file = File("day5/example.txt")

    val seeds = mutableListOf<Interval>()
    val reader = file.bufferedReader()
    val line = reader.readLine()
    val words = line.split(" ")
                for (i in 1 until words.size step 2) {
                    val start = words[i].toLong()
                    val len = words[i].toLong()
                    seeds.add(Interval(start, len))
                }

    reader.readLine()

    val list = MyMapList()
    list.read(reader)

    println(findLowestSeed(seeds, list))
}
