//my first ES6 code :)
'use strict';

class GeneticAlgorithm {
  constructor () {
    this._populationSize = 100;
  }
  
  generate (length) {
    let chrom = "";
    for (let i = 0; i < length; i++) {
      chrom += Math.round(Math.random()).toString();
    }
    return chrom;
  }
  
  select(population, fitnesses) {
    function selectOne() {
      //select probablity is proportional to the fitness of a chromosome
      let pointer = Math.random()*fitnesses.reduce((a,b) => a+b);
      
      let sum = 0;
      let i = 0;
      for (fit of fitnesses) {
        sum += fit;
        if( sum > pointer) break;
        i++;
      }
      
      return i;
    }
    
    let i1 = selectOne();
    let i2;
    while( (i2 = selectOne()) === i1) {} 
    
    return [population[i1], population[i2]];
  }
  
  mutate (chromosome, p) {
    return chromosome.split('').map( (bit) => {
      bit = parseInt(bit);
      return (Math.random() < p ? 1 - bit : bit);
    }).join('');
  }
  
  crossover (chrom1, chrom2) {
    let point = Math.floor(Math.random() * chrom1.length);
    newC1 = chrom1.slice(0,point).concat(chrom2.slice(point));
    newC2 = chrom2.slice(0,point).concat(chrom1.slice(point));
    return [newC1, newC2];
  }
  
  run (fitness, length, p_c, p_m, iterations = 100) {
    let population = [];
    let makeFitnesses = (population) => {
      return population.map((chrom) => fitness(chrom));
    }
    
    //make initial population
    while(population.length < this._populationSize) {
      population.push(this.generate(length));
    }
        
    for(let i = 0; i < iterations; i++) {
      let newPopulation = []
      while(newPopulation.length < this._populationSize) { 
        let chroms = this.select(population, makeFitnesses(population));
        
        //crossover occures with P = p_c
        if(Math.random() < p_c) {
            chroms = this.crossover(chroms[0], chroms[1]);
        }
        //mutation occurs with P = p_m
        chroms = chroms.map( chrom => this.mutate(chrom, p_m));

        newPopulation = newPopulation.concat(chroms);
      }
      
      population = newPopulation;
    }
    
    fitnesses = makeFitnesses(population);
    //return a chromosome with best fitness
    return population[ fitnesses.indexOf(Math.max.apply(Math,fitnesses))];
  }
}
